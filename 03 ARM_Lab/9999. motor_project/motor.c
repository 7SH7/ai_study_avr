#include "device_driver.h"
#include "motor.h"
#include <stdio.h>

#if 0

void MOTOR_Init(void)
{
    // PA0과 PA1을 출력으로 설정
    Macro_Write_Block(GPIOA -> MODER, 0xf, 0x5, IN_1A);
    GPIOA -> OTYPER &= ~(0x3 << IN_1A);
    GPIOA -> ODR &= ~(0x3 << IN_1A);
}

void motor_cw(void)
{
    // GPIOA -> ODR &= ~(0x1 << IN_1A);
    // GPIOA -> ODR |= 0x1 << IN_2A;
    Macro_Write_Block(GPIOA -> ODR, 0x3, 0x2, IN_1A);
}

void motor_ccw(void)
{
    // GPIOA -> ODR &= ~(0x1 << IN_2A);
    // GPIOA -> ODR |= 0x1 << IN_1A;
    Macro_Write_Block(GPIOA -> ODR, 0x3, 0x1, IN_1A);
}

void motor_stop(void)
{
    // GPIOA -> ODR &= ~(0x1 << IN_2A);
    // GPIOA -> ODR |= ~(0x1 << IN_1A);
    Macro_Clear_Area(GPIOA -> ODR, 0x3, IN_1A);
}

void motor_inverse(void)
{
    uint8_t tmp;
        printf("motor toggle");
        tmp = (~(GPIOA -> ODR)) & 0x3;
        motor_stop();
#if 1
        TIM2_Delay(1000);
        Macro_Write_Block(GPIOA -> ODR, 0x3, tmp, IN_1A);
#endif

#if 0
        TIM2_Oneshot(1000);
        if(Macro_Check_Bit_Set(TIM2 -> SR, 0))
        {
            Macro_Write_Block(GPIOA -> ODR, 0x3, tmp, IN_1A);
            // (i ^= 1) ? motor_cw() : motor_ccw();
            Macro_Clear_Bit(TIM2 -> SR, 0);
        }
#endif
}
#endif

#if 1

void MOTOR_Init(void)
{
    Macro_Write_Block(GPIOA -> MODER, 0xf, 0x5, 0);
	GPIOA->OTYPER &= ~(0x3 <<0) ;
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);

}

void motor_stop(void)
{
	//Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
    printf("stop");
    //TIM5_Out_Stop();
    // TIM5 -> CCER &= ~((0x3<<4)|(0x3<<0));
    Macro_Write_Block(TIM5 -> CCER, 0xff, 0x00, 0);
    // TIM5_Out_PWM_Generation(10000, 0, 0, 0);
}

void motor_ccw()
{
	//Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
    TIM5_Out_PWM_Generation(10000, 70, 1, 0);
}

void motor_cw()
{
	//Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
    TIM5_Out_PWM_Generation(10000, 70, 0, 1);
}

#endif

