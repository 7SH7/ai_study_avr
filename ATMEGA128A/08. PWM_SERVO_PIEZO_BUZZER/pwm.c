/*
 * pwm.c
 *
 * Created: 2026-06-18 오후 2:25:40
 *  Author: kccistc
 */ 

#include "button.h"

/*
16 BIT 1번 timer/counter를 사용

	PWM 출력 신호
	===============
	PB5 : OC1A : SERVO_MOTOR
	PB6 : OC1B : NOT USER
*/
void init_timer1_pwm(void);
int servo_motor_main(void);

void init_timer1_pwm(void) {
    // 모드 14 | 16bit 고속 PWM 모드 사용하겠다. timer1 ( P348 표 15-6)
    TCCR1A |= 1 << WGM11;    // TOP --> ICR1으로 설정한다.
    TCCR1B |= 1 << WGM12 | 1 << WGM13;

    // 비반전 모드 top : ICR1 비교일치 값 (PWM) 지정 OCR1A P350 표 15-7)
    // 비교 일치 발생 시 OCR1 의 출력핀은 LOW로 바뀌고 BOTTON에서 HIGH로 바뀐다.
    TCCR1A |= 1 << COM1A1;

    TCCR1B &= ~(1 << CS12 | 1 << CS11 | 1 << CS10); // all reset(기존값무시)
    TCCR1B |= 1 << CS11; // 분주비 8
    // OCR3C : 50 인 경우 Duty (HIGH)가 몇 % 인가?
    // Duty Cycle : (OCR3C / TOP) 100 = 50 / 255 * 100 = 19.61%

    ICR1 = 40000 - 1;
}

int servo_motor_main(void) {
    // servo motor가 PB5 출력으로 설정
    DDRB |= 1 << 5;
    init_timer1_pwm();

    // 0(1ms) --> 90 (1.5ms) --> 180 (2ms)
    while(1) {
        // 1ms : 2000개 count
        // 40000 (20ms) / 20 --> 1ms
        OCR1A=1000;
        _delay_ms(1000);

        OCR1A=3000;
//        OCR1A=2500;
        _delay_ms(1000);

        OCR1A=5000;
        _delay_ms(1000);
    }

    return 0;
}