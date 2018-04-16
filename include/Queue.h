#ifndef __QUEUE_H__
#define __QUEUE_H__ 

//Must specify the ElemType when include this file


#include "common.h"

typedef struct LinkNode
{
	ElemType data;
	struct LinkNode *next;
}LNode;

typedef struct Queue_
{
	LNode *rear, *front;
}Queue;

//Initialize queue with specific size
void InitQueue(Queue *Q, int size);
int IsEmpty(Queue *Q);
int IsFull(Queue *Q);
void EnQueue(Queue *Q, ElemType item);
ElemType DeQueue(Queue *Q);
ElemType GetHead(Queue *Q);
int Length(Queue *Q);

#endif