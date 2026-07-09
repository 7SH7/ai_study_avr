# 김승환 · 임베디드 SW 포트폴리오

> 서울상공회의소 **텔레칩스/넥스트칩 채용연계 반도체 SW·AI 개발자 과정 2기** (2026.05.27 개강)
> 목표 도메인: **차량용 SoC · 임베디드 SW · 비전/AI**

ATmega128A 기반 **베어메탈 C 펌웨어**로 주변장치(GPIO·타이머·인터럽트·ADC·UART·I2C)를
레지스터 레벨에서 직접 제어하고, 센서·모터·통신·디스플레이를 결합한 **통합 임베디드 프로젝트**를 진행했습니다.

---

## 🛠 기술 스택

| 구분 | 내용 |
|---|---|
| **MCU / 아키텍처** | ATmega128A (AVR, 8-bit), 베어메탈 (No Arduino/HAL) |
| **언어** | C (레지스터 직접 제어), 일부 자료구조(큐) 구현 |
| **주변장치** | GPIO, External/Timer Interrupt, Timer/Counter, PWM, ADC, UART, I2C |
| **센서/액추에이터** | HC-SR04 초음파, DC 모터(H-브릿지), 서보, 피에조, DHT11, DS1302/DS1307 RTC |
| **통신/HMI** | UART, Bluetooth(HC-06 계열), Character LCD, 4×4 Keypad, FND(7-seg) |
| **도구** | Microchip Studio, avr-gcc, KiCad(회로 설계), Git |
| **진행 예정** | STM32, Linux Device Driver, 차량용 SoC, OpenCV(영상처리) |

---

## 🚀 대표 프로젝트

### 1. [🚗 Auto Car — 초음파 자율주행차](ATMEGA128A/07.AUTO_CAR/) · *팀 프로젝트*
HC-SR04 3채널로 장애물을 감지해 자율 회피주행하고 Bluetooth로 수동조종도 가능한 4WD 차량.
`함수 포인터 기반 모드 FSM` · `INT4/5/6+Timer3 논블로킹 초음파` · `Timer1 고속 PWM 모터제어`
트러블슈팅: UART-FND 핀 충돌 → UART0 전환, `int` overflow → `uint32_t`.

### 2. [🧺 세탁기 컨트롤러 — 상태머신 설계](ATMEGA128A/06.MY_WASHING_MACHINE/)
대기→세탁→헹굼→탈수 + 시간설정 상태를 `enum FSM`으로 설계. 3버튼 입력, Timer0 기반 FND 카운트다운,
Timer3 PWM 모터. "시간 미설정 시 시작 불가" 같은 **상태 전이 제약조건**을 코드로 방어.

### 3. [🧮 RTC 탁상 계산기 — I2C·HMI·자료구조](ATMEGA128A/13.%20RTC_LCD_caculator/) · *팀 프로젝트*
DS1307 RTC(I2C, BCD 변환)로 시계를 표시하고, 4×4 키패드로 사칙연산 계산기를 구현.
`3모드 FSM(시계/계산기/시간수정)` · `Timer0 ISR 키패드 스캔 + 원형 큐 버퍼링` · `LCD 출력` · `60초 idle 타임아웃`.

> 📌 **기초 실습 모음**(주변장치 레지스터 실습 전체 인덱스)은 [ATMEGA128A/README.md](ATMEGA128A/) 참고.

---

## 📁 저장소 구조

```
ai_study_avr/
└─ ATMEGA128A/
   ├─ 01~05  LED · FND · Timer · UART · Ultrasonic   (기초 주변장치 실습)
   ├─ 06     Washing Machine / LED PWM               ★ 대표작
   ├─ 07     AUTO_CAR                                 ★ 대표작
   ├─ 08~12  Servo/Buzzer · DHT11 · DS1302 · Keypad · I2C
   └─ 13     RTC_LCD_Calculator                       ★ 대표작
```

---

## 👤 About

- **이름**: 김승환
- **관심 분야**: 차량용 임베디드 SW, 모터/센서 제어, 영상처리
- **Contact**: kimseunghwan7777@gmail.com

<!-- 향후: 각 프로젝트 시연 영상 링크, 블로그/노션 정리 링크 추가 예정 -->
