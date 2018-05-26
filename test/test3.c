#include <stdio.h>
#include <malloc.h>
#include "MGraph.h"

int main()
{
    MGraph *mg = (MGraph*)malloc(sizeof(MGraph));
    InitGraph(mg);
    CreateGraph(mg);
    PrintGraph(mg);

    BFS(mg);

    getchar();getchar();
    return 0;
}

/*
Test Edges
0 1 1
0 2 1
1 2 1
1 3 1
2 1 1
2 3 1
3 0 1
4 2 1
4 3 1
-1 -1 -1
*/