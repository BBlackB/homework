#include <stdio.h>
#include "BiTree.h"
#include <string.h>

int main()
{
    const char *TESTLIST = "1,2,4,8,#,#,9,#,#,5,10,#,#,#,3,6,#,#,7,#,#,";
    int arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    BiTNode *root;

    printf("Create tree by:\n");
    PrintArr(arr, 12);

    root = CreateTree(arr, 12);

    printf("\n\nAfter created tree.\n\n");

    printf("Preorder:\n");
    PreOrder(root);

    printf("\n\nInorder:\n");
    InOrder(root);

    printf("\n\nPostOrder:\n");
    PostOrder(root);

    printf("\n\nLayerOrder:\n");
    LayerOrder(root);

    printf("Serialize:\n\n");
    Serialize(root);

    PrintList();

    printf("Deserialize list is:\n");
    puts(TESTLIST);

    root = InvSequence(TESTLIST);

    printf("\n\nAfter Deserialize and PreOrder is:\n");
    PreOrder(root);

    getchar();
    return 0;
}