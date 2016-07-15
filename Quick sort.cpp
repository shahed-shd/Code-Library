// Algorithm    :   Quick sort.
// Complexity   :   O(n log n) on everage case, O(n^2) on worst case.

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10;

void quickSort(int arr[], int left, int right)
{
    int i = left, j = right, pivot = arr[(left+right)/2];

    // Partition.
    while(i <= j) {
        while(arr[i] < pivot) ++i;

        while(arr[j] > pivot) --j;

        if(i <= j) {
            swap(arr[i], arr[j]);
            ++i, --j;
        }
    }

    // Recursion.
    if(left < j)
        quickSort(arr, left, j);
    if(i < right)
        quickSort(arr, i, right);
}

int main()
{
    int arr[MAXN];

    for(int i = 0; i < MAXN; ++i)
        arr[i] = rand() % 100;

    puts("Before sorting:");
    for(auto &x : arr) printf("%d ", x);

    quickSort(arr, 0, MAXN-1);

    puts("\nAfter sorting:");
    for(auto &x : arr) printf("%d ", x);

    return 0;
}


// -------------------- Alternatively (different partitioning method) --------------------
/*
int partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left-1;                                 // Index of smaller element.

    for(int j = left; j < right; ++j)
        if(arr[j] <= pivot)                         // If current element is smaller than or equal to pivot.
            swap(arr[++i], arr[j]);

    swap(arr[++i], arr[right]);

    return i;
}

void quickSort(int arr[], int left, int right)
{
    if(left < right) {
        int index = partition(arr, left, right);    // Partitioning index, arr[index] is now at the right place.

        quickSort(arr, left, index-1);
        quickSort(arr, index+1, right);
    }
}
*/
