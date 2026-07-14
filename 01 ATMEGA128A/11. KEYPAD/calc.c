/*
 * calc.c
 *
 * Created: 2026-06-29 오후 4:15:19
 *  Author: kccistc
 */ 

double calculate(char* expression);

double calculate(char* expression)
{
	// stack에 담았다가 꺼내오는 방식..
	double operand_stack[32];
	char operator_stack[32];
	
	// 이전거랑 이번거랑 비교하려면 cnt 필요
	int operand_cnt = 0;
	int operator_cnt = 0;
	
	double current_num = 0;
	char last_operator = 0;
	
	while(*expression != '\0')
	{
		if('0' <= *expression && *expression <= '9')
		{
			current_num = (10 * current_num) + (*expression - '0');
			} else {
			if(last_operator == '*'){
				operand_stack[operand_cnt - 1] *= current_num;
			}
			else if(last_operator == '/'){
				operand_stack[operand_cnt - 1] /= current_num;
			}
			else {
				operand_stack[operand_cnt++] = current_num;
				if(last_operator != 0)  
				operator_stack[operator_cnt++] = last_operator;
			}
			
			last_operator = *expression;
			current_num = 0;
		}
		expression++;
	}
	
	if(last_operator == '*')
	{
		operand_stack[operand_cnt - 1] *= current_num;
	}
	else if(last_operator == '/')
	{
		operand_stack[operand_cnt - 1] /= current_num;
	}
	else
	{
		operand_stack[operand_cnt++] = current_num;
		if(last_operator != 0)
		operator_stack[operator_cnt++] = last_operator;
	}
	
	double result = operand_stack[0];
	for(int i = 0; i < operator_cnt; i++)
	{
		if(operator_stack[i] == '+')
		result += operand_stack[i + 1];
		else if(operator_stack[i] == '-')
		result -= operand_stack[i + 1];
	}
	return result;
}