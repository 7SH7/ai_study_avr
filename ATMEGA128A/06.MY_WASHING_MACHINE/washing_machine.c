/*
 * washing_machine.c
 *
 * Created: 2026-06-18 오후 4:18:56
 *  Author: kccistc
 */ 
#include "washing_machine.h"

extern void wash_running_express_led(void);
extern void rinse_running_express_led(void);
extern void spin_running_express_led(void);

extern int wash_running_express_fnd(int wash_time);

extern int current_fnd_washing_value;

int wash_running();
int rinse_running(void);
int spin_running(void);

extern void wash_running_dc_motor(void);
extern void rinse_running_dc_motor(void);
extern void spin_running_dc_motor(void);
extern void stop_dc_motor(void);

volatile int wash_time = 0;
volatile int rinse_time = 0;
volatile int spin_time = 0;

int wash_running()
{
	wash_running_express_led();

	// pwm 모터가 돌아가도록! >> 계속 호출되니, 자원 낭비..
	wash_running_dc_motor();
	
    if(current_fnd_washing_value <= 0)
	{
	    return 0;
	}
	return 1;
}

int rinse_running(void)
{
	rinse_running_express_led();
	
	rinse_running_dc_motor();

	if(current_fnd_washing_value <= 0)
	{
		return 0;
	}

	return 1;

}

int spin_running(void)
{
	spin_running_express_led();
	
	spin_running_dc_motor();

	if(current_fnd_washing_value <= 0)
	{
		return 0;
	}		

	return 1;

}

int stop_running(void)
{
	stop_dc_motor();
}