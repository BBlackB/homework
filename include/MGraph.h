#ifndef __MGRAGPH_H__
#define __MGRAGPH_H__

#define MAXVertex 100

#define ARRIVED 1
#define NOTARRIVED -1
#define NOTCONNECTED -1

typedef char VertexType;
typedef int EdgeType;

typedef struct 
{
    VertexType Vex[MAXVertex];
    EdgeType Edge[MAXVertex][MAXVertex];
    int vexnum, arcnum;
}MGraph;

void InitGraph(MGraph *G);

void CreateGraph(MGraph *G);

int Adjacent(MGraph *G, int x, int y);

void AddEdge(MGraph *G, int x, int y, int weight);

void RemoveEdge(MGraph *G, int x, int y);

void PrintGraph(const MGraph *G);

void Visit(const MGraph **G,int vex);

void BFS(const MGraph *G);

#endif