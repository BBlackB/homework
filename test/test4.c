#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "QSort.h"

#define ARRAY_LENGTH 1024
#define MAX_DATA 32767
#define MIN_DATA -32768

#define DEBUG

int main()
{
    int arr[ARRAY_LENGTH];
    int item, pos;
    clock_t start_time, end_time;

    GenData(arr, ARRAY_LENGTH, MIN_DATA, MAX_DATA);

    #ifdef DEBUG
    start_time = clock();
    #endif

    QSort(arr, 0, ARRAY_LENGTH - 1);

    #ifdef DEBUG
    end_time = clock();
    printf("time=%fms\n\n", (double)(end_time - start_time)/CLOCKS_PER_SEC * 1000);
    #endif

    PrintArr(arr, ARRAY_LENGTH);

    item = MIN_DATA + rand() % (MAX_DATA - MIN_DATA + 1);
    pos = BinSearch(arr, ARRAY_LENGTH, item);

    if (pos == -1)
        printf("\n\nCan't find the item(%d)\n", item);
    else
        printf("\n\nFind the item(%d), it's position is %d\n", item, pos);

    getchar();
    return 0;
}