#include "MGraph.h"
#include "Queue.h"
#include <string.h>

void InitGraph(MGraph *G)
{
    int i;
    G->vexnum = 0;
    G->arcnum = 0;
    memset(G->Vex, '\0', MAXVertex);
    for (i = 0;i < MAXVertex; i++)
        memset(G->Edge[i], NOTCONNECTED, MAXVertex*sizeof(int));
    for (i = 0; i < MAXVertex; i++) AddEdge(G, i,i, 0);
}

void CreateGraph(MGraph *G)
{
    int x, y, w;


    printf("Please input vertex number: ");
    scanf("%d", &(G->vexnum));
    getchar();

    printf("\n\nPlease input vertex name: \n");
    for (int i = 0; i < G->vexnum; i++) scanf("%c", &G->Vex[i]);

    printf("\n\nPlease input the edge: (x y weight)(end with -1)\n");
    while (1)
    {
        scanf("%d%d%d", &x, &y, &w);
        if (x <0 || y <0 || w < 0) break;
        AddEdge(G, x, y, w);
    }
}

void AddEdge(MGraph *G, int x, int y, int weight)
{
    G->Edge[x][y] = weight;
    G->arcnum++;
}

void RemoveEdge(MGraph *G, int x, int y)
{
    G->Edge[x][y] = 0;
}

void PrintGraph(const MGraph *G)
{
    int i, j;
    printf("Here are %d vertex.\n", G->vexnum);
    printf("There name are:");
    
    for (i = 0; i < G->vexnum; i++)
       printf("%c ", G->Vex[i]); 
    printf("\n");

    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            printf("%d ", G->Edge[i][j]);
        }
        printf("\n");
    }
}

void Visit(const MGraph **G,int vex)
{
    printf("visited: %c\n",(*G)->Vex[vex]);
}

void BFS(const MGraph *G)
{
    int currentVex;
    int notArrivedNum = G->vexnum;
    int bArried[MAXVertex];
    Queue Q;
    
    if (G->vexnum < 2) return;
    memset(bArried, ARRIVED, MAXVertex * sizeof(int));
    memset(bArried, NOTARRIVED, G->vexnum * sizeof(int));

       
    InitQueue(&Q, MAXVertex);
    EnQueue(&Q, 0);


    while (notArrivedNum)
    {
        currentVex = (int)DeQueue(&Q);
        Visit(&G, currentVex);
        bArried[currentVex] = ARRIVED;
        notArrivedNum--;
        for (int i = 0; i < G->vexnum; i++)
        {
            if (i == currentVex) continue;  //跳过自身
            if (bArried[i] == ARRIVED) continue; //已经到过了
            if (G->Edge[currentVex][i] == NOTCONNECTED) continue;   //两顶点之间不连通，跳过
            EnQueue(&Q, i);
        }
    }
}