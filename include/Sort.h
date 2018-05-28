#ifndef __SORT_H__
#define __SORT_H__

void GenData(int *data, int N, int min_data, int max_data);

int Partition(int *arr, int low, int high);

int qSort(int *arr, int low, int high);

int BinSearch(int *arr, int total, int item);

void AdjustHeap(int *arr, int node, int total);

void HeapSort(int *arr, int total, int times);

#endif