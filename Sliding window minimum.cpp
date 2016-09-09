// ==================================================
// Algorithm        :   Sliding window minimum.
// Time complexity  :   O(n)
// Reference Link   :   https://people.cs.uct.ac.za/~ksmith/articles/sliding_window_minimum.html
// Related problem  :   LightOJ 1093 - Ghajini
// ==================================================

#include <cstdio>
#include <deque>
using namespace std;

typedef     pair<int,int>       ii;

void sliding_window_minimum(int arr[], int n, int k)
{
    deque<ii> window;       // pair represents value & index.

    for(int i = 0; i < n; ++i) {
        while(!window.empty() && window.back().first >= arr[i])
            window.pop_back();
        window.push_back(ii(arr[i], i));

        while(window.front().second <= i - k)
            window.pop_front();

        printf("%d ", window.front().first);
    }
}

int main()
{
    int arr[] = {2, 4, 8, 6, 1, 9, 3, 7, 5, 10};

    int n = sizeof(arr) / sizeof(arr[0]);
    int windowSize = 3;

    puts("Minimum number in each window:");
    sliding_window_minimum(arr, n, windowSize);

    return 0;
}

/*
Output:

Minimum number in each window:
2 2 2 4 1 1 1 3 3 5
*/
