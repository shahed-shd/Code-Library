// Miller–Rabin primality test

#include <cstdio>
#include <cstdlib>
using namespace std;

typedef     long long       LL;

LL modular_pow(LL base, LL exponent, LL modulus)
{
    if(modulus == 1) return 0;

    LL result = 1;
    base %= modulus;

    while(exponent > 0) {
        if(exponent & 1) {
            result = (result * base) % modulus;
        }

        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;

}

LL modular_mul(LL a, LL b, LL modulus)
{
    LL result = 0;
    a %= modulus;

    while(b > 0) {
        if(b & 1) {
            result = (result + a) % modulus;
        }

        a = (2 * a) % modulus;
        b >>= 1;                            // b /= 2.
    }

    return result % modulus;
}

bool isPrime(LL n, int iteration)
{
    if(n < 2) return false;
    if(n <= 3) return true;
    if(!(n & 1)) return false;              // If n is even.

    LL d = n-1;                             // d * 2^r = n-1 where d is odd and r > 0.
    while(!(d & 1))
        d >>= 1;

    while(iteration--) {                    // Witness loop.
        LL a = rand() % (n-1) + 1;
        LL x = modular_pow(a, d, n);        // x = a^d % n
        LL d1 = d;

        while(d1 != n-1 && x != 1 && x != n-1) {
            x = modular_mul(x, x, n);       // This statement can be replaced with   x = modular_pow(x, 2, n).
            d1 <<= 1;
        }

        if(x != n-1 && !(d1 & 1)) {
            return false;
        }
    }

    return true;
}

int main()
{
    LL n;

    while(scanf("%lld", &n) != EOF)
        (isPrime(n, 5))? puts("Yes") : puts("No");

    return 0;
}
