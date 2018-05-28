#include "QSort.h"

void GenData(int *data, int N, int min_data, int max_data)
{
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        data[i] = min_data + rand() % (max_data - min_data + 1);
    }
}

int Partition(int *arr, int low, int high)
{
    int privot = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= privot)high--;
        arr[low] = arr[high];
        while (low < high && arr[low] <= privot)low++;
        arr[high] = arr[low];
    }
    arr[low] = privot;
    return low;
}

void QSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int flag = Partition(arr, low, high);
        QSort(arr, low, flag-1);
        QSort(arr, flag+1, high);
    }

}

int BinSearch(int *arr, int total, int item)
{
    int low = 0, high = total - 1;
    int k;
    if (item < arr[0] || item > arr[total-1]) return -1;
    while (low <= high)
    {
        k  = (low + high)/2;
        if (arr[k] == item) return k;
        if (item > arr[k]) low = k + 1;
        else high = k - 1;
    }
    return -1;
}