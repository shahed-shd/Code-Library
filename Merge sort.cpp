#include <iostream>
using namespace std;

int const MAXN = 20;

int arr[MAXN] = {5, 3, 7, 8, 2, 9, 0, 1, 6, 4};
int temp[MAXN];

void mergeSort(int left, int right)
{
    if(left == right) return;   // Only one element is considered to be sorted.

    // Divide.
    int mid = (left + right) / 2;

    mergeSort(left, mid);
    mergeSort(mid+1,right);

    // Merge.
    int i = left, j = mid+1;

    for(int k = left; k <= right; ++k) {
        if(i <= mid && (arr[i] < arr[j] || j > right))
            temp[k] = arr[i++];
        else
            temp[k] = arr[j++];
    }

    // Copy.
    for(int k = left; k <= right; ++k)
        arr[k] = temp[k];
}

int main()
{
    for(int i = 0; i < MAXN; ++i)
        arr[i] = rand() % 100;

    cout << "Before sorting:\n";

    for(int i = 0; i < MAXN; ++i)
        cout << ' ' << arr[i];

    mergeSort(0, MAXN-1);

    cout << "\nAfter sorting:\n";

    for(int i = 0; i < MAXN; ++i)
        cout << ' ' << arr[i];

    return 0;
}
