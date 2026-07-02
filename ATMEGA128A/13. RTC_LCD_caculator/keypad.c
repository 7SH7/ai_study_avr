/*
 * keypad.c
 *
 * Created: 2026-07-02 오후 2:22:33
 *  Author: kccistc
 */ 
#include "keypad.h"
void init_keypad(void);
uint8_t get_button_k(int row, int col);
uint8_t keypad_scan(void);

void init_keypad(void)
{
	KEYPAD_DDR = 0x0f; // row:입력  col : 출력
	KEYPAD_PORT = 0xff;
	BUZZER_DDR |= (1 << BUZZER_PIN);
}

uint8_t keypad_scan(void)
{
	uint8_t data = 0; //key값 저장 변수
	
	for (int row = 0; row<4; row++)
	{
		for(int col = 0; col <4; col++)
		{
			data = get_button_k(row,col);
			if(data)   //if data >= 1
			return data;
		}
	}
}

uint8_t get_button_k(int row, int col)
{
	#if 0
	uint8_t keypad_char[4][4] = {
		{'+', '0', '=', },
		{'*', '6', '5', '4'},
		{'/', '9', '8', '7'},
		{'-', '3', '2', '1'}
	};
	#else
	uint8_t keypad_char[4][4] = {
		{'0', '=', '+', },
		{'4', '5', '6', '*'},
		{'7', '8', '9', '-'},
		{'1', '2', '3', '/'}
	};
	#endif
	//ACTIVE-LOW로 동작
	static int8_t prev_state[4][4] =
	{
		{
			{1,1,1,1},
			{1,1,1,1}, //초기버튼은 눌려지지 않은 상태로 한다.
			{1,1,1,1},
			{1,1,1,1}
		}
	};
	
	int8_t current_state = 1;
	
	KEYPAD_PORT = 0xff;
	KEYPAD_PORT &= ~(1 << 3 - col); //3-col : COL4가 PA0에 연결되어있기 때문에
	//KEYPAD_PORT &= ~(1 << col); //해당 col에 전류를 흘린다.
	
	for(int delay = 0; delay < 20; delay++);//keypad check를 위한 delay
	// 0.625us x 20 = 1.25us
	current_state = (KEYPAD_PIN & (1 << (row + 4))) >> (row + 4);
	
	//ex row:0 PA4에 연결
	//76543210
	//11101111 KEYPAD_PIN & (1 << (row + 4))
	//00001110 >> (row+4)
	if ( current_state == 0 && prev_state [row][col] == 1)  //처음 눌러진 상태
	{
		prev_state [row][col] = 0;
		return 0;
	}
	else if(current_state == 1 && prev_state [row][col] == 0)
	{ //이전에 버튼이 눌려지고 버튼을 뗀 상태이면 버튼을 1번 눌렀다 뗀것으로 인정
		prev_state [row][col] = 1; //prev_state를 초기화
		printf("key : %c\n",  keypad_char[row][col]);
		return keypad_char[row][col];
	}
	
	return 0;
}

void buzzer_beep(void)
{
	for(int i = 0; i < 40; i++) // 40번 반복 (소리 길이 조절 가능)
	{
		BUZZER_PORT |= (1 << BUZZER_PIN);  // High
		_delay_us(400);
		BUZZER_PORT &= ~(1 << BUZZER_PIN); // Low
		_delay_us(400);
	}
}