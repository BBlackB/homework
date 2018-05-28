#include <stdio.h>
#include <time.h>
#include "Sort.h"

#define ARRAY_LENGTH 1024
#define MAX_DATA 32767
#define MIN_DATA -32768
#define HEAPTIMES 10

#define DEBUG

int main()
{
    int arr[ARRAY_LENGTH];
    clock_t start_time, end_time;
    
    GenData(arr, ARRAY_LENGTH, MIN_DATA, MAX_DATA);
    #ifdef DEBUG
    start_time = clock();
    #endif

    HeapSort(arr, ARRAY_LENGTH, HEAPTIMES);

    #ifdef DEBUG
    end_time = clock();
    printf("time=%fms\n\n", (double)(end_time - start_time)/CLOCKS_PER_SEC * 1000);     //0.074ms vs 0.021ms
    #endif


    printf("The smallest %d numbers is: ", HEAPTIMES);
    for (int i = ARRAY_LENGTH-HEAPTIMES; i < ARRAY_LENGTH; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    getchar();
    return 0;
}