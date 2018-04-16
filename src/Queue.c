#include <stdio.h>
#include "../include/Queue.h"
#include <malloc.h>

//Initialize queue with specific size
void InitQueue(Queue *Q, int size)
{
	LNode *head, *q;
	LNode *p = (LNode *)malloc(sizeof(LNode));
	p->data = NULL;
	head = p;
	q = p;
	while(size--)
	{
		p = (LNode *)malloc(sizeof(LNode));
		//Initialize data with default value
		p->data = NULL;
		q->next = p;
		q = p;
	}
	//Circulat linked list
	p->next = head;
	//Initialize queue
	Q->rear = head;
	Q->front = head;
}

int IsEmpty(Queue *Q)
{
	return Q->rear == Q->front;
}

int IsFull(Queue *Q)
{
	return Q->rear->next == Q->front;
}

void EnQueue(Queue *Q, ElemType item)
{
	Q->rear->data = item;
	Q->rear = Q->rear->next;
}

ElemType DeQueue(Queue *Q)
{
	ElemType item;
	item = Q->front->data;
	Q->front = Q->front->next;
	return item;
}

ElemType GetHead(Queue *Q)
{
	return Q->front->data;
}

int Length(Queue *Q)
{
	int len = 0;
	LNode *p = Q->front;
	
	while(p != Q->rear) 
	{
		p = p->next;
		len++;
	}
	return len;
}