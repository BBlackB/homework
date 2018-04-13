#ifndef __QUEUE_H__
#define __QUEUE_H__ 

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
int EnQueue(Queue *Q, ElemType item);
int DeQueue(Queue *Q, ElemType *item);
int GetHead(Queue *Q, ElemType *item	);

#endif