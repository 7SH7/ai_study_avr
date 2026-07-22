/*
 * queue.ccircular_front
 *
 * Created: 2026-06-29 오후 3:19:49
 *  Author: kccistc
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_MAX 100

int circular_front=-1;   // read index
int circular_rear=-1;    // insert index
uint8_t queue[QUEUE_MAX];

int queue_full(void)
{
	// queue에서 circular_rear+1 % QUEUE_MAX의 값이 circular_front와 같으면 queue full
	int tmp=(circular_rear+1) % QUEUE_MAX;
	if (tmp == circular_front)  // circular_front와 같으면 queue full
		return TRUE;
	else return FALSE;	
}

int queue_empty()
{
	if (circular_rear == circular_front)  // circular_front와 같으면 queue empty
		return TRUE;
	else return FALSE;	
}

uint8_t read_queue()
{
	if (queue_empty())
		printf("Queue is empty !!!\n");
	else
	{
		circular_front = (circular_front+1) % QUEUE_MAX;
		return (queue[circular_front]);
	}
}

void queue_init()  // queue가 텅 빈경우 fron와 circular_rear가 동일한 위치를 가리틴다.
{
	circular_front=-1;   // read index
	circular_rear=-1;    // insert index	
}

void insert_queue(uint8_t value)
{
	if (queue_full())
	{
		printf("queue full!!!!\n");
		return;
	}
	else   // save 
	{
		circular_rear = (circular_rear+1) % QUEUE_MAX;
		queue[circular_rear]=value;
	}
}