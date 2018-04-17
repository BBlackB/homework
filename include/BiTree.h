#ifndef __BITREE_H__
#define __BITREE_H__ 

#include "common.h"
#include "Queue.h"
#include <malloc.h>

#define BTElemType int
#define MAX_SIZE_QUEUE 128

typedef struct BiTreeNode
{
	BTElemType data;
	struct BiTreeNode *lchild, *rchild;
}BiTNode;

BiTNode* CreateTree(BTElemType *arr, int size);

void visit(BiTNode *BTree);

void PreOrder(BiTNode *BTree);

void InOrder(BiTNode *BTree);

void PostOrder(BiTNode *BTree);

void LayerOrder(BiTNode *BTree);

int Serialize(BiTNode *BTree);

BiTNode* InvSequenceHelper();

BiTNode* InvSequence(const char *buf);

void InvInOrder(BiTNode *BTree, int *buf, int size);

void InitList();

void PrintList();

void PrintArr(int *buf, int size);

char saveList[MAX_SIZE_QUEUE * MAX_SIZE_QUEUE];

#endif