#include <stdio.h>
#include "../include/test1.h"
#include "../include/Queue.h"
#include <malloc.h>

int main()
{
	int size, i, x;
	Queue *buf = (Queue *)malloc(sizeof(Queue));

	printf("Input the size of buffer: ");
	scanf("%d", &size);
	InitQueue(buf, size);
	for (i = 0; i < size; i++)
	{ 
		if (!IsFull(buf))
			EnQueue(buf, (void *)i);
		else
			printf("EnQueue Error!\n");
	}

	printf("Length = %d\n", Length(buf));

	if (IsFull(buf))
		printf("Insert Error!\n");

	for (i = 0; i < size; i++)
	{
		if (!IsEmpty(buf))
		{
			x = (int)DeQueue(buf);
			printf("%d ", x);
		}
		else
		{
			printf("DeQueue Error!\n");
		}
	}
		if (!IsEmpty(buf))
		{
			x = (int)DeQueue(buf);
			printf("%d ", x);
		}
		else
		{
			printf("DeQueue Error!\n");
		}
	return 0;
}