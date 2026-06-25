/*
 * 08. PWM_SERVO_PIEZO_BUZZER.c
 *
 * Created: 2026-06-25 오전 9:46:40
 * Author : kccistc
 */ 

extern const int Elise_Tune[];
extern const int Elise_Beats[];

extern const int drum_washing_stop_melody_Tune[];
extern const int drum_washing_stop_melody_Beats[];

#include "button.h"

#if 1
extern void power_on_melody();
extern void open_buzzer();
extern void drum_washing_stop_melody(int* tone, int* Beats);

volatile uint32_t ms = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;	// TCNT0 6~256: 250개 pulse count 하기 위해
	ms++;	// 1ms count
	//	ultrasonic_check_time++;
}

int main(void)
{
	init_button();
	init_speaker();
	init_timer0();
	
	sei();
	while(1)
	{
		if(get_button(BUTTON0, BUTTON0PIN))
		{
			power_on_melody();
		}
		else if(get_button(BUTTON1, BUTTON1PIN))
		{
			open_buzzer();
		}
		else if(get_button(BUTTON2, BUTTON2PIN))
		{
			drum_washing_stop_melody(drum_washing_stop_melody_Tune, drum_washing_stop_melody_Beats);
		}
	}
}

init_timer0(void)
{
	TCNT0 = 6;	// TCNT0 0~256 : 250개 pulse count 위해

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);	// 0분주
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;	// 64분주
	
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT
	sei();	// 전역(대문)
}



#endif

#if 0	// piezo buzzer
extern void init_speaker();

int main(void)
{
	init_speaker();
	
	/* Replace with your application code */
	while (1)
	{
		//OCR3A=1702;
		//_delay_ms(1000);
		//OCR3A=1431;
		//_delay_ms(1000);
		
//		Beep(5);
		//RRR();
		//_delay_ms
		Music_Player(Elise_Tune, Elise_Beats);
	}
}



#endif

#if 0	// servo motor
#include <avr/io.h>

extern int servo_motor_main(void);

int main(void)
{
	servo_motor_main();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}


#endif