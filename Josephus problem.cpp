// Josephus problem.
// Related link:    http://e-maxx.ru/algo/joseph_problem

#include <cstdio>
using namespace std;

/*
int josephus(int n, int k)      // Time complexity: O(k log(n)). Efficient for small k.
{                               // In 0 based indexing.
    if (n == 1)  return 0;
    if (k == 1)  return n-1;
    if (k > n)  return (josephus(n-1, k) + k) % n;

    int cnt = n / k;
    int res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0) res += n;
    else res += res / (k - 1);

    return res;
}
*/

int josephus(int n, int k)          // Time complexity: O(n).
{                                   // In 0 based indexing, that is, n persons with id: 0, 1, 2, ..., n-1.
    int winner = 0;

    for(int i = 2; i <= n; ++i) {
        winner += k;
        if(winner >= i) winner %= i;
    }

    return winner;
}

int main()
{
    int n = 100, k = 5;

    int w = josephus(n, k);

    printf("The winner is %d\n", w+1); // Output in 1 based indexing.

    return 0;
}
