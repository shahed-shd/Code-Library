// Bitwise operations

#include <cstdio>
using namespace std;

typedef     unsigned long long      ULL;

int ilog2(ULL n)
{
    int i = -1;

    if(n & 0xffffffff00000000) { i += 32; n >>= 32; }

    if(n & 0xffff0000) { i += 16; n >>= 16; }

    if(n & 0xff00) { i += 8; n >>= 8; }

    if(n & 0xf0) { i += 4; n >>= 4; }

    if(n & 0b1100) { i += 2; n >>= 2; }

    if(n & 0b10) { i += 1; n >>= 1; }

    if(n) ++i;

    return i;
}

int main()
{
    printf("%d\n", ilog2(1023));        // output: 9

    return 0;
}
