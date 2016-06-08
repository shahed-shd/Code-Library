// Modular exponentiation - Right-to-left binary method.
// Time complexity : O(log exponent).
// Reference link: https://en.wikipedia.org/wiki/Modular_exponentiation

#include <cstdio>
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

int main()
{
    LL base = 4;
    LL exponent = 13;
    LL modulus = 497;

    printf("base: %lld, exponent: %lld, modulus: %lld\n", base, exponent, modulus);
    printf("result = (b to the power e) %% m = %lld\n", modular_pow(base, exponent, modulus));

    return 0;
}

/*
Output:

base: 4, exponent: 13, modulus: 497
result = (b to the power e) % m = 445
*/
