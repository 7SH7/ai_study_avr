# 🧮 RTC 탁상 계산기 — I2C RTC · LCD · 키패드 HMI

> ATmega128A · 베어메탈 C · I2C(DS1307) + Character LCD + 4×4 Keypad + 큐 자료구조 · **팀 프로젝트**

| 구분 | 내용 |
|---|---|
| **한 줄 소개** | DS1307 RTC로 시계를 표시하고, 키패드로 사칙연산 계산기를 쓰는 탁상형 멀티기능 장치 |
| **MCU / 환경** | ATmega128A (16 MHz, 베어메탈) · Microchip Studio |
| **핵심 기술** | 3모드 FSM · **I2C RTC(BCD 변환)** · Timer0 ISR 키패드 스캔 · **원형 큐 입력버퍼** · LCD 출력 · idle 타임아웃 |
| **담당 역할** | RTC(I2C)·LCD·모드 FSM·시간설정 담당 / 계산기·키패드는 팀원 |

---

## 1. 개요
하나의 장치에서 **시계(RTC) / 계산기 / 시간 수정** 세 가지 모드를 버튼으로 전환한다.
시간은 I2C RTC 칩(DS1307)에서 읽어 LCD에 표시하고, 계산기 모드에서는 4×4 키패드 입력으로 사칙연산을 수행한다.

## 2. 동작 모드 FSM
```
        BTN4                     BTN3
 RTC_CLOCK ───────► CALCULATOR   RTC_CLOCK ⇄ RTC_CHG_MODE
  (시계 표시)        (키패드 계산)   (시간 수정: BTN2로 항목 선택 yy→mm→dd→hh→min→sec,
                                                BTN0/1로 값 −/＋)
```
| 모드 | 설명 |
|------|------|
| `RTC_CLOCK` | DS1307에서 시각 read → LCD에 달력/시계 출력 |
| `CALCULATOR` | 키패드 입력을 큐에 쌓아 사칙연산 처리, 60초 무입력 시 시계로 복귀 |
| `RTC_CHG_MODE` | 연·월·일·시·분·초 항목별 증감으로 시간 설정 |

## 3. 핵심 구현 포인트

### 3.1 I2C DS1307 RTC — BCD ↔ Decimal 변환
- DS1307은 시간을 **BCD**로 저장 → 읽을 때 `bcd2dec`, 쓸 때 `dec2bcd` 변환 필요
- 시각 정보를 `t_ds1307` 구조체(sec/min/hour/date/month/year/ampm/hourmode)로 캡슐화
```c
typedef struct { uint8_t seconds, minutes, hours, date, month, dayofweek, year, ampm, hourmode; } t_ds1307;
```

### 3.2 Timer0 ISR 키패드 스캔 + 원형 큐 버퍼링
```c
ISR(TIMER0_OVF_vect){
    TCNT0 = 6;
    if (program_stat == CALCULATOR){
        idle_counter++;
        if (++keypad_counter >= 60){                 // 주기적 스캔 (약 60 tick마다)
            keypad_counter = 0;
            uint8_t k = keypad_scan();
            if (k != 0) insert_queue(k);             // 입력을 큐에 적재 (ISR은 짧게)
        }
    }
}
```
→ ISR에서는 **스캔·큐 적재만** 하고, 실제 계산은 메인 루프(`cal_main`)에서 처리 → ISR을 짧게 유지.

### 3.3 idle 타임아웃
- 계산기 모드에서 `idle_counter`가 `TIMEOUT_MS(60초)` 초과 시 자동으로 시계 모드로 복귀 (사용성).

### 3.4 파일 구성
| 파일 | 역할 |
|---|---|
| `main.c` | 3모드 FSM, 버튼 입력 처리, 시간 항목 증감 |
| `ds1307.c` | I2C RTC read/write, BCD 변환, 달력 출력 |
| `i2c_m_loopback.c / i2c_master.c` | I2C 마스터 통신 계층 |
| `keypad.c` | 4×4 키패드 스캔 |
| `queue.c` | 원형 큐(입력 버퍼) 자료구조 |
| `calc.c` | 계산기 로직(입력 파싱·연산) |
| `lcd.c` | Character LCD 드라이버 |
| `uart0.c` | UART(printf 리다이렉트, PC 디버그) |

## 4. 요소 기술
- **I2C 프로토콜**: 마스터-슬레이브, 주소지정, START/STOP, ACK — 실습용 loopback으로 검증 후 RTC에 적용
- **자료구조**: 키 입력을 순서대로 처리하기 위한 **원형 큐(front/rear)**
- **HMI 설계**: 다중 버튼 + 키패드 + LCD를 하나의 상태 흐름으로 통합

## 5. 결과물
- 🎥 시연 영상: `video.mp4`
- 📄 발표자료: `team14.pptx`
- 💻 소스: 본 폴더

## 6. 👤 담당 역할 / 개인 기여

- **본인 담당**: DS1307 RTC(I2C 통신 · BCD↔dec 변환) · Character LCD 출력(데이터시트 기반 초기화 시퀀스) · 3-모드 FSM(시계/계산기/시간수정)과 시간 설정 로직 · Timer0 ISR 스캔 스케줄링 · idle 타임아웃 · UART(printf 디버그).
- **팀원 담당**: 계산기 연산 로직(`calc.c`) · 4×4 키패드 스캔(`keypad.c`).
- **직접 해결한 이슈**: BTN4 미배선 상태에서 입력이 여러 번 눌러야 넘어가던 문제 → 배선/코드 정리로 해결. *(세부 이슈는 본인 확인 후 보완)*

## 7. 배운 점
- RTC 칩의 **BCD 포맷**과 I2C 통신 절차를 데이터시트 기반으로 구현
- ISR은 짧게(스캔·적재), 무거운 처리는 메인 루프로 분리하는 **인터럽트 설계 원칙**
- 큐 자료구조로 입력을 버퍼링해 **입력과 처리를 분리**

## 8. 면접 예상 질문 & 답변 포인트 (코드 근거)

| 질문 | 답변 포인트 (근거) |
|------|-------------------|
| DS1307에서 시간을 왜 변환해서 읽나? | RTC가 시간을 **BCD**로 저장 → 읽을 때 `bcd2dec`, 쓸 때 `dec2bcd`. 시각을 `t_ds1307` 구조체로 캡슐화. |
| 키패드를 왜 Timer0 ISR에서 스캔하나? | ISR에서는 **주기 스캔 + 큐 적재만**(짧게), 실제 계산은 메인 루프(`cal_main`)에서. → ISR을 짧게 유지하는 원칙. |
| 원형 큐를 쓴 이유는? | 키 입력(생산)과 계산 처리(소비)를 **분리·버퍼링**하기 위해 front/rear 원형 큐 사용. |
| 3개 모드를 어떻게 전환하나? | `program_stat`(RTC_CLOCK/CALCULATOR/RTC_CHG_MODE) + `chg_clock_stat`(yy~sec) 2단 FSM. 버튼별 역할 분리. |
| 사용성 고려는? | 계산기 모드에서 `idle_counter`가 60초(TIMEOUT_MS) 초과 시 자동으로 시계 모드 복귀. |