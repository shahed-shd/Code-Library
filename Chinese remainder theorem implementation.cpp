#include <cstdio>
using namespace std;

typedef     long long       LL;

void extEuclid(LL a, LL b, LL &x, LL &y, LL &gcd)
{
    x = 0, y = 1, gcd = b;
    LL m, n, q, r;

    for(LL u = 1, v = 0; a != 0; gcd = a, a = r) {
        q = gcd / a; r = gcd % a;
        m = x-u*q; n = y-v*q;
        x = u; y = v; u = m; v = n;
    }
}

LL modInv(LL n, LL m)
{
    LL x, y, gcd;
    extEuclid(n, m, x, y, gcd);
    if(gcd == 1) return (x % m);
    return 0;
}

LL chinese_remainder_theorem(int num[], int rem[], int k)
{
    LL prod = 1;

    for(int i = 0; i < k; ++i)
        prod *= num[i];

    LL res = 0;                             // res = sum(rem[i] * pp[i] * inv[i]) % prod.   [0 <= i <= k-1]
                                            // here, pp[i] = prod/num[i]    and    inv[i] = (1/pp) % num[i].
    for(int i = 0; i < k; ++i) {
        LL pp = prod / num[i];

        LL inv = modInv(pp, num[i]);
        if(inv < 0) inv += num[i];

        res += rem[i] * pp * inv;
        res %= prod;
    }

    return res;
}

int main()
{
    int num[] = {3, 4, 5};          // Numbers in num[] must be pairwise coprime (gcd for every pair is 1).
    int rem[] = {2, 3, 1};
    int k = sizeof(num) / sizeof(num[0]);

    LL N = chinese_remainder_theorem(num, rem, k);

    printf("N : %lld\n", N);        // N % num[i] = rem[i], [0 <= i <= k-1].

    return 0;
}

/*

Output:
N : 11

That is,
11 % 3 = 2,
11 % 4 = 3,
11 % 5 = 1.

As, 3 * 4 * 5 = 60.
Here, 11 is the minimum solution.
(11 + any multiple of 60) also can be the solution,
like 71, 131, 191, . . . .

*/
