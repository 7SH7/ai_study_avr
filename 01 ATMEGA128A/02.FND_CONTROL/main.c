/*
 * 02.FND_CONTROL.c
 *
 * Created: 2026-06-12 오전 10:44:01
 * Author : kccistc
 */ 

#include <avr/io.h>

extern void init_fnd(void);
extern void find_display(void);
extern int fnd_main(void);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		fnd_main();
    }
}

