// Modular Multiplicative Inverse - Iterative method.
// Time complexity: O(log m).

#include <cstdio>
using namespace std;

void extEuclid(int a, int b, int &x, int &y, int &gcd)
{
    x = 0; y = 1; gcd = b;
    int m, n, q, r;

    for (int u = 1, v = 0; a != 0; gcd = a, a = r) {
        q = gcd / a; r = gcd % a;
        m = x-u*q; n = y-v*q;
        x = u; y = v; u = m; v = n;
    }
}

// The result could be negative, if it's required to be positive, then add 'm'.
int modInv(int n, int m)
{
    int x, y, gcd;
    extEuclid(n, m, x, y, gcd);
    if (gcd == 1) return x % m;
    return 0;
}


int main()
{
    int a = 14;
    int b = 11;
    int m = 26;

    int res = ((a%m) * modInv(b, m)) % m;   // (a/b) % m.
    if(res < 0) res += m;

    printf("res : %d\n", res);

    return 0;
}


// Extended Euclidean Algorithm - Recursive method.
/*

int x, y, gcd;

void extEuclid(int a, int b)
{
	if (b == 0) { x = 1, y = 0, gcd = a; return; }

	extEuclid(b, a % b);
	x = x - (a / b) * y;
	swap(x, y);
}

*/
