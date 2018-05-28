#ifndef __QSORT_H__
#define __QSORT_H__

void GenData(int *data, int N, int min_data, int max_data);

int Partition(int *arr, int low, int high);

int qSort(int *arr, int low, int high);

int BinSearch(int *arr, int total, int item);

#endif