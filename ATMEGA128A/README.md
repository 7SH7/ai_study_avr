# ATmega128A 펌웨어 기초 실습 모음

> 베어메탈 C로 AVR 주변장치를 **레지스터 레벨**에서 직접 제어한 실습 인덱스.
> 데이터시트(핀맵·레지스터·인터럽트 벡터)를 근거로 하나씩 구현하며 통합 프로젝트(★)로 확장했다.

## 📇 주변장치별 실습 인덱스

| # | 폴더 | 주변장치 / 주제 | 핵심 개념 |
|---|------|----------------|-----------|
| 01 | `01.LED_CONTROL` | GPIO 입출력 | DDR/PORT/PIN, 풀업/풀다운, 버튼 입력 |
| 02 | `02.FND_CONTROL` | 7-seg FND | 소프트웨어 멀티플렉싱, 시계/스톱워치, 상태머신 ([README](02.FND_CONTROL_MY_0612/)) |
| 03 | `03.TIMER_CONTROL` | Timer/Counter | 분주, 오버플로우, 주기 이벤트 (FND+버튼 통합, [README](03.TIMER_FND_BTN_CONTROL_MY_0615/)) |
| 04 | `04. UART` | UART | 비동기 통신, 보레이트, `printf` 리다이렉트 |
| 05 | `05.ULTRASONIC` | HC-SR04 초음파 | 트리거/에코, 인터럽트+타이머 펄스폭 측정 |
| 06 | `06.DCMOTOR_PWM_CONTROL` | PWM · DC 모터 | Fast PWM, 듀티, H-브릿지 방향제어 |
| 08 | `08. PWM_SERVO_PIEZO_BUZZER` | 서보 · 피에조 | PWM 각도제어, 주파수 사운드 |
| 09 | `09. DHT11` | 온습도 센서 | 단선(1-wire) 타이밍 프로토콜 |
| 10 | `10. DS1302` | RTC (3-wire) | 실시간 시계, BCD, 시리얼 인터페이스 |
| 11 | `11. KEYPAD` | 4×4 키패드 | 행/열 스캔, 디바운싱 |
| 12 | `12.I2C_M_LOOPBACK` / `12.I2C_S_LOOPBACK` | I2C 마스터/슬레이브 | START/STOP, 주소지정, ACK, loopback 검증 |

## ⭐ 통합 프로젝트 (별도 상세 README)

| 폴더 | 프로젝트 | 결합 요소 |
|------|----------|-----------|
| [`06.MY_WASHING_MACHINE`](06.MY_WASHING_MACHINE/) | 세탁기 컨트롤러 | FSM · Timer · PWM · FND |
| [`07.AUTO_CAR`](07.AUTO_CAR/) | 초음파 자율주행차 | 초음파×3 · PWM 모터 · UART/BT · FND · FSM |
| [`13. RTC_LCD_caculator`](13.%20RTC_LCD_caculator/) | RTC 탁상 계산기 | I2C RTC · LCD · 키패드 · 큐 |

## 🧭 학습 흐름
GPIO → 타이머/인터럽트 → 통신(UART/I2C) → 센서/액추에이터 → **통합 프로젝트**
순서로, 개별 주변장치를 익힌 뒤 하나의 제품 형태로 결합하는 것을 목표로 진행했다.

---

## 🎤 주변장치별 면접 핵심 포인트 (제어쟁이 커뮤니티 지식 기반)

> 아래 실습에서 다룬 주변장치를 "동작만"이 아니라 **원리·오개념 방지** 관점으로 정리(면접 대비).
> 실제 구현 수준과 별개로, 각 개념을 설명할 수 있어야 함.

| 주변장치 | 면접에서 짚어야 할 핵심 |
|---------|------------------------|
| GPIO | "1을 쓴다" = 레지스터 설정→출력드라이버→물리핀. **Push-Pull vs Open-Drain**(I2C는 Open-Drain+풀업), Alternate Function |
| 버튼 입력 | **바운스**(접점 튐)와 **Pull-up/down**(floating 방지)은 다른 문제. 디바운싱으로 1회 입력 확정 |
| Timer | 시간 재기가 아니라 클럭→Counter→event/PWM. **Prescaler·ARR·CCR**(=AVR의 분주·TOP·비교값) |
| 인터럽트 | ISR은 **짧게**(flag만), delay 금지. NVIC/EXTI 우선순위, 에지/레벨 |
| 폴링 vs 인터럽트 | 폴링=주기 확인(단순), 인터럽트=놓치면 안 되는 이벤트. 설계 선택 |
| ADC | 채널·**샘플링 시간**·분해능·**Vref**·오차. R 큰 RC 필터는 샘플링 캡 충전 부족 유발 |
| PWM | 듀티로 평균전압. 모터/LED. 전력효율·노이즈 이점(vs PAM) |
| UART | 비동기, **8N1**, TX↔RX 교차, TTL≠RS232, 연속수신엔 DMA/ring buffer |
| I2C | SDA/SCL, **주소·START/STOP·ACK/NACK**, **Open-Drain+풀업**, 버스 capacitance |
| RTC(DS1302/DS1307) | 시간은 **BCD** 저장 → dec 변환. DS1302=3-wire, DS1307=I2C |
| 초음파(HC-SR04) | 트리거→에코 펄스폭으로 거리. **인터럽트+타이머 캡처**로 논블로킹 측정 |

> 데이터시트 읽기 5단계(제어쟁이): ① 목차로 지도 ② 핀맵/Alternate Function 먼저 확정 ③ 전기적 특성(전류·전압 한계) ④ 클록트리·타이밍 ⑤ 레지스터(reset값·W1C·Reserved=0).
