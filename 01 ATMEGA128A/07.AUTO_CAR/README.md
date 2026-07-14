# 🚗 Auto Car — 초음파 센서 기반 AVR 자율주행차

> ATmega128A · 베어메탈 C · 초음파 3채널 장애물 회피 + Bluetooth 수동제어 · **팀 프로젝트**

| 구분 | 내용 |
|---|---|
| **한 줄 소개** | HC-SR04 3개로 전방/좌/우 장애물을 감지해 스스로 회피 주행하고, Bluetooth로 수동 조종도 가능한 4WD 차량 |
| **MCU / 환경** | ATmega128A (16 MHz, 베어메탈) · Microchip Studio · KiCad(회로도) |
| **핵심 기술** | 모드 FSM · 함수 포인터 디스패치 · 인터럽트 기반 초음파 측정 · Timer1 고속 PWM · UART/Bluetooth |
| **담당 역할** | 펌웨어 전반 직접 설계·구현 (모드 FSM·초음파 인터럽트·PWM·트러블슈팅) · 팀 프로젝트 |

---

## 1. 개요

초음파 센서로 전방 장애물을 감지하고 **AVR MCU 기반 FSM 제어**로 자율주행하는 차량. Bluetooth 통신으로
**Manual Mode**(원격 조종)와 **Auto Mode**(자율 회피주행)를 지원한다.

**개발 목표**: 거리 기반 장애물 회피 · 좌/우 독립 PWM 모터제어 · UART(BT) 수동제어 · FND 2개로 주행시간·실행횟수 표시 · 버튼 모드 전환.

## 2. 하드웨어 구성

| 부품 | 모델 | 용도 |
|------|------|------|
| MCU | ATmega128A | 메인 제어 |
| 초음파 ×3 | HC-SR04 | 전방·좌·우 거리 측정 |
| 모터 드라이버 | HW-095 (L298 계열) | DC 모터 H-브릿지 |
| DC 모터 ×4 | DG01D | 4WD 구동 |
| Bluetooth | ZS-040 (HC-06) | 수동 명령 송수신 |
| FND ×2 | CL5642AH42 | 주행시간 / 실행횟수 |
| 버튼·LED | - | 모드 전환 / 상태 표시 |
| 배터리 | INR-18650-35E | 모터 구동 전원 |

> 회로도: KiCad `auto_car.kicad_sch`

## 3. 시스템 아키텍처

### 3.1 동작 모드 FSM
```
[전원 ON] → MANUAL(BT 원격) ⇄(BTN) AUTO(자율회피)
 MANUAL: BT Rx 'F/B/L/R/S' → 즉시 주행/정지
 AUTO  : 좌/중/우 거리값으로 다음 방향 자동 결정
```

### 3.2 함수 포인터 기반 모드 디스패치
```c
void (*fp_mode[])(void) = { manual_mode, auto_mode, auto_mode_check, distance_check };
while (1) {
    fp_mode[func_state]();                       // 현재 모드 핸들러 실행
    if (get_button(BUTTON, BUTTONPIN))           // 버튼으로 모드 토글
        func_state = (func_state == 1) ? 0 : 1;
}
```
→ 모드 추가 시 분기문이 아니라 배열에 핸들러만 추가 → **확장 가능한 구조**.

### 3.3 파일 구성
| 파일 | 역할 |
|---|---|
| `main.c` | 슈퍼루프, 모드 FSM, 함수 포인터 디스패치 |
| `ultrasonic.c` | HC-SR04 트리거 + INT4/5/6·Timer3 에코 캡처 |
| `pwm.c` | Timer1 고속 PWM, 방향(H-브릿지), forward/back/turn/stop |
| `uart0.c / uart1.c` | UART/Bluetooth 송수신 |
| `fnd.c / washing_machine.c` | FND 멀티플렉싱 출력 |
| `timer.c / button.c / led.c` | 1ms 틱 / 버튼 이벤트 / 상태 LED |

## 4. 핵심 구현 포인트 (면접 설명용)

### 4.1 인터럽트 기반 초음파 거리 측정 (Non-blocking)
`_delay`로 에코를 기다리지 않고, **외부 인터럽트(INT4/5/6) + Timer3**로 에코 펄스 폭을 측정한다.
```c
ISR(INT4_vect){                       // 왼쪽 센서 에코
    if (ECHO_PORT & (1<<ECHO_PIN_L)) start_time_l = TCNT3;      // 상승 에지: 시작 시각
    else {                                                     // 하강 에지: 펄스폭→거리
        uint16_t t = TCNT3 - start_time_l;
        int dist = (t * 1000000.0 * 1024 / F_CPU) / 58;        // us → cm
        if (dist > 0 && dist < 400) ultrasonic_distance_l = dist;
        flag_l = 1;
    }
}
```
- 3센서를 **순차 트리거 → 이전 완료(flag) 후 다음 트리거**하는 상태머신으로 상호 간섭 없이 스캔
- CPU가 에코 대기로 멈추지 않아 주행 제어 루프가 끊기지 않음

### 4.2 회피 판단 + 방향 유지(hold)
```c
if (hold_count > 0) { hold_count--; return; }              // 회전/후진을 일정 시간 유지
if      (dist_c < 15) { car_direction = CAR_BACK;  hold_count = 60; }
else if (dist_l < 16) { car_direction = CAR_RIGHT; hold_count = 30; }
else if (dist_r < 14) { car_direction = CAR_LEFT;  hold_count = 30; }
else                    car_direction = CAR_FORWARD;
```
→ 센서값이 순간적으로 튀어도 방향이 떨리지 않도록 **최소 유지 사이클**을 둔 것이 포인트.

### 4.3 Timer1 고속 PWM 모터 제어
- Fast PWM 모드 14, `ICR1 = 0x3FF`(TOP), 분주 64 → 주기 약 4 ms
- `OC1A(PB5)`=좌륜, `OC1B(PB6)`=우륜 듀티로 속도, `PORTF0~3`(H-브릿지 IN1~4)로 방향
- 좌/우 듀티를 다르게 줘서 제자리 회전 구현

## 5. 트러블슈팅 (핵심 어필)

| # | 문제 | 원인 | 해결 |
|---|------|------|------|
| 1 | UART1(PD2/3) 사용 시 FND 4번째 자리 오동작 | UART1 핀과 FND 핀 **자원 충돌** | UART1 → **UART0 전환**, 업로드/동작 결선 절차 분리 |
| 2 | 모터 구동 중 FND 깜빡임 | FND 초기화가 PORTF `0~7` 일괄 초기화 → 모터용 `PF0~3` 침범 | FND는 `PF4~7`, 모터는 `PF0~3`만 **분리 초기화** |
| 3 | 특정 주기로 직진↔후진 반복 | 시간 변수 `int` → µs 누적값 **overflow로 음수화** | 자료형 **`uint32_t`로 변경** |

> 세 건 모두 "되냐"가 아니라 **제한 자원에서 원인을 구조적으로 분석하고 대안을 택한** 사례.

## 6. 요소 기술
Polling vs Interrupt 역할 분리 · Bluetooth FHSS(625µs 채널 호핑) · PWM vs PAM 채택 근거.

## 7. 결과물
- 🎥 시연 영상: Manual / Auto / FND (`3조_*.mp4`)
- 📄 발표자료: `3조_...Auto_Car.pptx.pdf`
- 🔌 회로도(KiCad) · 💻 소스(`07.AUTO_CAR/`)

## 8. 👤 담당 역할 / 개인 기여

> 팀 프로젝트. 아래는 **본인이 직접 설계·구현**한 부분.

- **담당 모듈**: 펌웨어 전반 — 모드 FSM + 함수 포인터 디스패치, 초음파 3채널 인터럽트(INT4/5/6)+Timer3 논블로킹 측정, Timer1 고속 PWM 모터제어, UART/Bluetooth 통신, FND 표시.
- **직접 해결한 트러블**: UART1↔FND 핀 충돌(→UART0 전환) · 모터 구동 중 FND 깜빡임(PORTF 분리 초기화) · `int` overflow로 인한 직진↔후진 버그(→`uint32_t`).
- **팀 내 역할**: 펌웨어 설계·구현·통합 주도.

## 9. 배운 점
- `_delay` 블로킹 대신 인터럽트+타이머로 **다중 센서 논블로킹 처리**
- 데이터시트(핀맵·타이머·인터럽트 벡터) 근거로 레지스터 직접 설정
- 자료형 overflow·핀 자원 충돌 등 **하드웨어 제약을 코드로 방어**

## 10. 면접 예상 질문 & 답변 포인트 (코드 근거)

> 제어쟁이가 강조한 "면접관은 설계 이유·디버깅을 묻는다"에 맞춰, 실제 코드 근거로 정리.

| 질문 | 답변 포인트 (근거) |
|------|-------------------|
| 초음파를 왜 인터럽트로 처리했나? polling과 차이는? | `_delay`로 에코를 기다리면 그동안 주행 루프가 멈춘다. INT4/5/6 외부인터럽트 + Timer3로 에코 펄스폭만 측정 → **논블로킹**. ISR은 "에지 시각 기록 / 거리 환산"만(짧게 유지). |
| 초음파 3개가 서로 간섭하지 않게 한 방법은? | 동시에 쏘면 에코가 섞인다 → `distance_check` 상태머신으로 **순차 트리거**, 이전 센서 완료 flag 확인 후 다음 트리거. |
| 직진↔후진이 주기적으로 반복된 버그, 원인과 해결은? | 시간 측정 변수를 `int`로 선언 → µs 누적값이 자료형 범위를 넘어 **overflow로 음수화** → 직진 조건에서도 후진. `uint32_t`로 변경해 해결. (자료형 범위) |
| UART1 대신 UART0를 쓴 이유는? | UART1 핀(PD2/PD3)이 FND 제어 핀과 **하드웨어 충돌**(데이터시트 핀맵 확인) → UART0로 전환, 업로드/동작 결선 절차 분리. |
| 모드 전환을 왜 함수 포인터 배열로? | `if/else` 나열 대신 `fp_mode[func_state]()` → 모드 추가가 배열 확장으로 끝나는 **확장 구조**. |
| 회피 방향이 흔들리지 않게 한 방법은? | 센서값이 순간적으로 튀어도 `hold_count` **최소 유지 사이클**로 회전/후진을 일정 시간 유지. |
| PWM으로 방향·속도를 어떻게 제어했나? | Timer1 Fast PWM(모드14, ICR1=0x3FF), `OC1A/OC1B` 듀티=속도, `PORTF0~3`(H-브릿지 IN1~4)=방향, 좌우 듀티차로 회전. |