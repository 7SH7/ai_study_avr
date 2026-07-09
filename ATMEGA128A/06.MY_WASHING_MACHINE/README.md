# 🧺 세탁기 컨트롤러 — FSM 기반 임베디드 제어

> ATmega128A · 베어메탈 C · 상태머신(FSM) 설계 실습 프로젝트

| 구분 | 내용 |
|---|---|
| **한 줄 소개** | 대기→세탁→헹굼→탈수 사이클과 각 단계 시간설정을 버튼으로 제어하는 세탁기 펌웨어 |
| **MCU / 환경** | ATmega128A (16 MHz, 베어메탈) · Microchip Studio |
| **핵심 기술** | `enum` 기반 FSM · Timer0 FND 멀티플렉싱/카운트다운 · Timer3 PWM 모터 · 버튼 이벤트 처리 |

---

## 1. 개요
실제 세탁기의 동작 흐름을 **유한 상태 기계(FSM)**로 모델링했다. 사용자가 세탁/헹굼/탈수 시간을 설정하고
시작하면, 각 단계가 타이머로 카운트다운되며 자동으로 다음 단계로 전이된다.

## 2. 상태 정의 (FSM)
```
                 ┌─────────── standby (대기) ───────────┐
        BTN1     │   BTN0(start, 단 세 시간 모두 설정 시)  │  BTN0(정지)
   ┌────────────▼──────────┐                             │
   │ wash_time_set          │  wash → rinse → spin →  standby
   │ → rinse_time_set       │   (각 단계 시간 0 되면 자동 전이)
   │ → spin_time_set        │   BTN2: 분(min) 증가
   └────────────────────────┘
```
| 상태 | 설명 |
|------|------|
| `standby_state` | 대기 (LED off) |
| `wash/rinse/spin_state` | 세탁·헹굼·탈수 실행 (LED 패턴 + PWM 모터 + FND 카운트다운) |
| `*_time_set` | 각 단계 시간 설정 (BTN2로 분 증가) |

## 3. 핵심 구현 포인트

### 3.1 상태 전이 제약조건 방어
```c
if (machine_state == standby_state && wash_time && rinse_time && spin_time) {
    machine_state = wash_state;      // 세 단계 시간이 모두 설정돼야만 시작 허용
}
```
→ "시간 미설정 시 시작 불가" 같은 **비정상 입력을 상태 전이 단계에서 차단**.

### 3.2 시간 종료 이벤트로 자동 전이
```c
if (machine_state == wash_state && !wash_running()) {   // 카운트다운 종료
    machine_state = rinse_state;
    current_fnd_washing_value = rinse_time * 60;         // 다음 단계 초기화
}
```
→ 각 단계 실행 함수가 남은 시간을 반환하고, 0이 되면 다음 상태로 넘어가는 **틱 기반 이벤트 구조**.

### 3.3 Timer0 ISR에서 FND + 1초 카운트다운
```c
ISR(TIMER0_OVF_vect){
    TCNT0 = 6;  static int ms = 0;
    if (is_use_timer_set_status)          time_set_fnd(current_fnd_setting_value);   // 설정값 표시
    else if (is_use_timer_running_washmach){
        wash_running_express_fnd(current_fnd_washing_value);                         // 멀티플렉싱 출력
        if (++ms >= 1000){ if (current_fnd_washing_value>0) current_fnd_washing_value--; ms=0; }  // 1초마다 감소
    } else fnd_all_off();
}
```

### 3.4 파일 구성
| 파일 | 역할 |
|---|---|
| `main.c` | FSM 상태 전이(버튼 입력 + 시간종료 이벤트) |
| `washing_machine.c` | 각 단계 실행(LED/모터/FND 갱신, 남은시간 반환) |
| `fnd.c / timer.c` | FND 멀티플렉싱, Timer0 1ms 틱 |
| `pwm.c / led.c / button.c` | Timer3 PWM 모터, 상태 LED, 버튼 디바운싱 |

## 4. 배운 점 / 개선 여지
- 사이클 전체를 **상태도 → 코드 1:1 대응**으로 설계하는 감각
- (개선) `wash_running()`이 매 루프 모터 재설정을 호출 → 자원 낭비. 상태 진입 시 1회만 설정하도록 리팩터링 여지
- (개선) `standby`에서 실행 플래그를 매 루프 초기화 → 진입 시 1회 처리로 정리 가능

> ℹ️ 개인/과제 프로젝트 여부와 담당 범위가 다르면 이 절에 역할을 명시하세요.

## 5. 면접 예상 질문 & 답변 포인트 (코드 근거)

| 질문 | 답변 포인트 (근거) |
|------|-------------------|
| 상태를 어떻게 정의·전이했나? | `enum WashingMachineStatus`로 standby/wash/rinse/spin + 시간설정 상태를 명시. 버튼 입력과 "시간 종료 이벤트" 두 축으로 전이. |
| 시작을 아무 때나 못 하게 한 제약은? | `standby && wash_time && rinse_time && spin_time`일 때만 wash 진입 → **비정상 입력을 전이 단계에서 차단**. |
| 단계가 자동으로 넘어가는 구조는? | 각 단계 실행 함수가 남은 시간을 반환, `current_fnd_washing_value<=0`이면 다음 상태로. (틱 기반 이벤트) |
| Timer0 ISR은 무슨 일을 하나? | `TCNT0=6`으로 1ms 틱, FND 멀티플렉싱 출력 + `ms>=1000`마다 남은 시간 1초 감소. |
| FND를 왜 인터럽트로 갱신하나? | 메인 루프가 버튼/상태 처리에 묶여도 화면이 끊기지 않도록 주기 갱신을 ISR로 분리(멀티플렉싱은 일정 주기 필수). |

- 세탁 모터를 단순 on/off가 아니라 **PWM 속도 프로파일**(가속/감속)로 제어.
- (리팩터링) 상태 진입 시 1회만 모터/플래그 설정하도록 구조 개선(현재는 매 루프 재호출 → 자원 낭비).
