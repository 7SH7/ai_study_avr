/*
 * calc.c
 *
 * Created: 2026-07-02 오후 2:19:29
 *  Author: kccistc
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"
#include "LCD.h"
#include "button.h" 

#define MAX_EXPR_LEN 40

extern void LCD_write_data(uint8_t data);
extern void LCD_write_string(char *str);
extern void LCD_goto_XY(uint8_t row, uint8_t col);
extern void LCD_clear(void);
extern int get_button(int button_num, int button_pin);
extern uint8_t is_queue_empty(void);
extern uint8_t delete_queue(void);
extern void buzzer_beep(void);
// 내부 전역 변수
static char expr_buffer[MAX_EXPR_LEN];
static int expr_idx = 0;
static uint8_t is_calculated = 0; 

// 내부 함수 프로토타입 선언
static int32_t eval_expression(const char* expr, int* valid);
static int get_precedence(char op);
static int32_t apply_op(char op, int32_t b, int32_t a, int* valid);
static int check_parentheses(const char* expr);
static void refresh_calculator_lcd(void);
static void clear_calculator_state(void);

typedef enum {
	RTC_CLOCK,
	CALCULATOR,
	RTC_CHG_MODE
} program_stat_t;
extern program_stat_t program_stat;

/**
 * @brief 수식 버퍼 내용을 기반으로 LCD 화면을 2줄로 나누어 실시간 갱신
 */
static void refresh_calculator_lcd(void)
{
    LCD_clear();
    
    // 1. 1~16번째 글자는 첫 번째 줄(row 0)에 출력
    LCD_goto_XY(0, 0);
    for (int i = 0; i < expr_idx && i < 16; i++)
    {
        LCD_write_data(expr_buffer[i]);
    }
    
    // 2. 17번째 글자부터는 두 번째 줄(row 1)에 이어서 출력 (자동 줄바꿈)
    if (expr_idx > 16)
    {
        LCD_goto_XY(1, 0);
        for (int i = 16; i < expr_idx && i < MAX_EXPR_LEN; i++)
        {
            LCD_write_data(expr_buffer[i]);
        }
    }
}

/**
 * @brief 계산기 내부 버퍼 및 상태 변수 초기화
 */
static void clear_calculator_state(void)
{
    LCD_clear();
    memset(expr_buffer, 0, sizeof(expr_buffer));
    expr_idx = 0;
    is_calculated = 0;
}

/**
 * @brief 키패드 입력을 받아 계산기 기능을 수행하는 메인 프로세싱 함수
 */
void calculator_processing(uint8_t key)
{
    // [기능 1] 리셋/취소 버튼 ('C')
    if (key == 'C' || key == 'c') 
    {
        clear_calculator_state();
        printf("\r[Calc] Reset\n");
        return;
    }

    // [기능 2] 계산 완료 상태에서 새로운 키가 들어오면 화면 및 버퍼 초기화 후 입력 시작
    if (is_calculated)
    {
        clear_calculator_state();
    }

    // [기능 3] 백스페이스 버튼 ('B')
    if (key == 'B' || key == 'b') 
    {
        if (expr_idx > 0) 
        {
            expr_idx--;
            expr_buffer[expr_idx] = '\0';
            refresh_calculator_lcd(); 
            printf("\r[Calc] BS. Current: %s\n", expr_buffer);
        }
        return;
    }

    // [기능 4] 일반 입력 문자 처리 (숫자, 사칙연산자, 괄호)
    if ((key >= '0' && key <= '9') || key == '+' || key == '-' || 
        key == '*' || key == '/' || key == '(' || key == ')')
    {
        if (expr_idx < MAX_EXPR_LEN - 1)
        {
            expr_buffer[expr_idx++] = key;
            expr_buffer[expr_idx] = '\0';
            
            refresh_calculator_lcd(); // 실시간 글자수 체크 및 줄바꿈 반영
            printf("%c", key);
        }
    }
    // [기능 5] 결과 산출 버튼 '='
    else if (key == '=')
    {
        printf("=\n");

        // 1. 괄호 쌍 유효성 검사
        if (!check_parentheses(expr_buffer))
        {
            LCD_clear();
            LCD_goto_XY(0, 0);
            LCD_write_string("Error: Parentheses");
            printf(" Error: Parentheses Mismatch\r\n");
            is_calculated = 1; 
            return;
        }

        // 2. 수식 연산 엔진 구동
        int valid = 1;
        int32_t result = eval_expression(expr_buffer, &valid);

        // 3. 결과 출력을 위한 화면 정리 및 출력
        LCD_clear();
        LCD_goto_XY(0, 0);
        LCD_write_string("Result:");

        LCD_goto_XY(1, 0);
        if (!valid)
        {
            LCD_write_string("Error: Div by 0");
            printf(" Error: Division By Zero\r\n");
        }
        else
        {
            char result_str[16];
            sprintf(result_str, "%ld", result);
            LCD_write_string(result_str);
            printf("Ans: %ld\r\n", result);
        }

        is_calculated = 1; // 연산 완료 상태 마킹
    }
}

/**
 * @brief 수식의 괄호 쌍 매칭 상태를 검사합니다.
 */
static int check_parentheses(const char* expr) 
{ 
    int count = 0; 
    for (int i = 0; expr[i] != '\0'; i++) 
    { 
        if (expr[i] == '(') count++; 
        else if (expr[i] == ')') 
        { 
            count--; 
            if (count < 0) return 0; 
        } 
    } 
    return (count == 0); 
}

/**
 * @brief 사칙연산자의 우선순위를 반환합니다.
 */
static int get_precedence(char op) 
{ 
    if (op == '+' || op == '-') return 1; 
    if (op == '*' || op == '/') return 2; 
    return 0; 
}

/**
 * @brief 지정된 이항 연산을 수행합니다. (0 나누기 체크 포함)
 */
static int32_t apply_op(char op, int32_t b, int32_t a, int* valid) 
{ 
    switch (op) 
    { 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': 
            if (b == 0) 
            { 
                *valid = 0; 
                return 0; 
            } 
            return a / b; 
    } 
    return 0; 
}

/**
 * @brief 중위 표기법(Infix) 수식 문자열을 파싱하여 결과를 계산합니다.
 */
static int32_t eval_expression(const char* expr, int* valid) 
{ 
    int32_t val_stack[MAX_EXPR_LEN]; 
    char op_stack[MAX_EXPR_LEN]; 
    int val_top = -1; 
    int op_top = -1; 

    for (int i = 0; expr[i] != '\0'; i++) 
    { 
        if (expr[i] == ' ') continue; 

        // 1. 숫자가 연달아 나오는 경우 피연산자로 묶어서 숫리스택에 push
        if (isdigit((unsigned char)expr[i])) 
        { 
            int32_t val = 0; 
            while (expr[i] != '\0' && isdigit((unsigned char)expr[i])) 
            { 
                val = (val * 10) + (expr[i] - '0'); 
                i++; 
            } 
            i--; 
            val_stack[++val_top] = val; 
        } 
        // 2. 여는 괄호는 연산자 스택에 push
        else if (expr[i] == '(') 
        { 
            op_stack[++op_top] = expr[i]; 
        } 
        // 3. 닫는 괄호 처리: 여는 괄호를 만날 때까지 누적 연산 진행
        else if (expr[i] == ')') 
        { 
            while (op_top >= 0 && op_stack[op_top] != '(') 
            { 
                int32_t val2 = val_stack[val_top--]; 
                int32_t val1 = val_stack[val_top--]; 
                char op = op_stack[op_top--]; 
                
                val_stack[++val_top] = apply_op(op, val2, val1, valid); 
                if (!(*valid)) return 0; 
            } 
            if (op_top >= 0) op_top--; // 여는 괄호 제거
        } 
        // 4. 일반 연산자 처리: 이전 연산자와 우선순위를 비교하여 처리
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') 
        { 
            while (op_top >= 0 && get_precedence(op_stack[op_top]) >= get_precedence(expr[i])) 
            { 
                int32_t val2 = val_stack[val_top--]; 
                int32_t val1 = val_stack[val_top--]; 
                char op = op_stack[op_top--]; 
                
                val_stack[++val_top] = apply_op(op, val2, val1, valid); 
                if (!(*valid)) return 0; 
            } 
            op_stack[++op_top] = expr[i]; 
        } 
    } 

    // 5. 문자열 순회가 끝난 후 스택에 남아있는 잔여 연산 완결
    while (op_top >= 0) 
    { 
        int32_t val2 = val_stack[val_top--]; 
        int32_t val1 = val_stack[val_top--]; 
        char op = op_stack[op_top--]; 
        
        val_stack[++val_top] = apply_op(op, val2, val1, valid); 
        if (!(*valid)) return 0; 
    } 

    // 최종 결과 반환
    return (val_top == 0) ? val_stack[val_top] : 0; 
}

/**
 * @brief main.c를 슬림화하기 위한 계산기 모드 통합 제어 함수
 * @param idle_cnt main.c의 무입력 타이머 카운터 포인터
 * @param timeout_max 제한 시간 (60000ms)
 * @param mode_var 현재 시스템 모드 변수 포인터 (타임아웃 시 시계로 변경용)
 */
void cal_main(uint32_t *cnt, uint32_t timeout, int program_stat)
{
    static uint8_t l_btn0 = 0, l_btn1 = 0, l_btn2 = 0, l_btn3 = 0;

    // 1. 1분간 무입력 타임아웃 검사
    if (*cnt >= timeout)
    {
        program_stat = RTC_CLOCK; // MODE_CLOCK (0)으로 복귀
        LCD_clear();
        printf("\r\n[Timeout! Back to Clock Mode]\r\n");
        return;
    }

    // 2. 상단 독립 기능 버튼 스캔 (C, B, (, ) 처리)
    uint8_t btn0 = get_button(BUTTON0, BUTTON0PIN);
    uint8_t btn1 = get_button(BUTTON1, BUTTON1PIN);
    uint8_t btn2 = get_button(BUTTON2, BUTTON2PIN);
    uint8_t btn3 = get_button(BUTTON3, BUTTON3PIN);

    if (btn0 && !l_btn0) { calculator_processing('C'); *cnt = 0; }
    if (btn1 && !l_btn1) { calculator_processing('B'); *cnt = 0; }
    if (btn2 && !l_btn2) { calculator_processing('('); *cnt = 0; }
    if (btn3 && !l_btn3) { calculator_processing(')'); *cnt = 0; }

    l_btn0 = btn0; l_btn1 = btn1; l_btn2 = btn2; l_btn3 = btn3;

    // 3. 키패드 매트릭스로부터 큐에 쌓인 입력 데이터가 있는지 검사
	if (!is_queue_empty())
	{
		uint8_t key = delete_queue();
		*cnt = 0;
		
		buzzer_beep();              // 키패드 입력이 버퍼에서 처리될 때 부저 가동!
		
		calculator_processing(key);
	}
}