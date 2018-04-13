#include <stdio.h>
#include "../include/Queue.h"
#include <malloc.h>

//Initialize queue with specific size
void InitQueue(Queue *Q, int size)
{
	LNode *head, *q;
	LNode *p = (LNode *)malloc(sizeof(LNode));
	p->data = 0;
	head = p;
	q = p;
	while(size--)
	{
		p = (LNode *)malloc(sizeof(LNode));
		//Initialize data with default value
		p->data = 0;
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

int EnQueue(Queue *Q, ElemType item)
{
	if (IsFull(Q))
		return 0;
	Q->rear->data = item;
	Q->rear = Q->rear->next;
	return 1;
}

int DeQueue(Queue *Q, ElemType *item)
{
	if (IsEmpty(Q))
		return 0;
	*item = Q->front->data;
	Q->front = Q->front->next;
	return 1;
}

int GetHead(Queue *Q, ElemType *item)
{
	if (IsEmpty(Q))
		return 0;
	*item = Q->front->data;
	return 1;
}