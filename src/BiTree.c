#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BiTree.h"

BiTNode* CreateTree(BTElemType *arr, int size)
{
	int i;
	BiTNode  **pNode, *node;
	BiTNode *BTree = (BiTNode *)malloc(sizeof(BiTNode));
	
	if (size == 0)
		return NULL;
		
	Queue Q;
	InitQueue(&Q, MAX_SIZE_QUEUE);
	EnQueue(&Q, &BTree);

	for (i = 0; i < size; i++)
	{
		pNode = DeQueue(&Q);
		node = (BiTNode *)malloc(sizeof(BiTNode));
		node->data = arr[i];
		EnQueue(&Q, &node->lchild);
		EnQueue(&Q, &node->rchild);
		*pNode = node;
	}

	while (!IsEmpty(&Q))
	{
		pNode = DeQueue(&Q);
		pNode = NULL;
	}
	
	return BTree;
}

void visit(BiTNode *BTree)
{
	//TODO
	if (BTree)
		printf("%d ", BTree->data);
	else
		printf("* ");
}


void PreOrder(BiTNode *BTree)
{
	if (BTree)
	{
		visit(BTree);
		PreOrder(BTree->lchild);
		PreOrder(BTree->rchild);
	}
}

void InOrder(BiTNode *BTree)
{
	if (BTree)
	{
		InOrder(BTree->lchild);
		visit(BTree);
		InOrder(BTree->rchild);
	}
}

void PostOrder(BiTNode *BTree)
{
	if (BTree)
	{
		PostOrder(BTree->lchild);
		PostOrder(BTree->rchild);
		visit(BTree);
	}
}

void LayerOrder(BiTNode *BTree)
{
	BiTNode *p;
	Queue Q;
	
	if(!BTree)
		return ;
	
	InitQueue(&Q, MAX_SIZE_QUEUE);
	EnQueue(&Q, BTree); 

	while (!IsEmpty(&Q))
	{
		p = DeQueue(&Q);
		visit(p);
		if (p->lchild) EnQueue(&Q, p->lchild);
		if (p->rchild) EnQueue(&Q, p->rchild);
	}
}

int Serialize(BiTNode *BTree)
{
	//TODO
	if (!BTree)
		sprintf(saveList, "%s#,", saveList);
	else
	{
		sprintf(saveList, "%s%d,", saveList, BTree->data);
		Serialize(BTree->lchild);
		Serialize(BTree->rchild);
	}

	return 0;
}

BiTNode* InvSequenceHelper()
{
	//TODO
	char *tmp = strtok(NULL, ",");
	if (!strcmp(tmp, "#")) return NULL;
	BiTNode *root = (BiTNode *)malloc(sizeof(BiTNode));
	root->data = atoi(tmp);
	root->lchild = InvSequenceHelper();
	root->rchild = InvSequenceHelper();
	return root;
}

//by preorder
BiTNode* InvSequence(const char *buf)
{
	//TODO
	//useless code!!
	char *tmp;
	char buf1[MAX_SIZE_QUEUE * MAX_SIZE_QUEUE];
	strcpy(buf1, buf);
	sprintf(buf1, "!,%s", buf);
	tmp = strtok(buf1, ",");
	
	return InvSequenceHelper();
}

void InitList()
{
	strcpy(saveList, "");
}

void PrintList()
{
	char *tmp;
	char cplist[MAX_SIZE_QUEUE * MAX_SIZE_QUEUE];
	
	strcpy(cplist, saveList);
	printf("\n\nThe list is:\n");
	tmp = strtok(cplist, ",");
	while (tmp)
	{
		printf("%s ", tmp);
		tmp = strtok(NULL, ",");
	}

	printf("\n\n");
}

void PrintArr(int *buf, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", buf[i]);
	printf("\n");
}