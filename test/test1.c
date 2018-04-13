#include <stdio.h>
#include "../include/Queue.h"
#include <malloc.h>

int main()
{
	int size, i, x;
	Queue *buf = (Queue *)malloc(sizeof(Queue));
	printf("Input the size of buffer: ");
	scanf("%d", &size);
	InitQueue(buf, size);
	for (i = 0; i < size; i++) EnQueue(buf, i);

	for (i = 0; i < size; i++) { DeQueue(buf, &x); printf("%d ", x);}

	return 0;
}