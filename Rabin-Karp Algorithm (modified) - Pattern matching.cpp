// Modified Rabin-Karp algorithm by usign two times hashing.
// It can be applied not only on strigns but also on array of integers.

#include <iostream>
using namespace std;

typedef     long long       LL;

const int BASE1 = 31, MOD1 = 1e9+7, BASE2 = 37, MOD2 = 1e9+9;

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

void search_by_hashing(string &txt, string &pat)
{
    int n = txt.size(), m = pat.size();

    LL h1 = modular_pow(BASE1, m-1, MOD1), h2 = modular_pow(BASE2, m-1, MOD2);
    LL hTxt1 = 0, hTxt2 = 0, hPat1 = 0, hPat2 = 0;     // Hash values.

    for(int i = 0; i < m; ++i) {
        hPat1 = (hPat1 * BASE1 + pat[i]) % MOD1;
        hPat2 = (hPat2 * BASE2 + pat[i]) % MOD2;

        hTxt1 = (hTxt1 * BASE1 + txt[i]) % MOD1;
        hTxt2 = (hTxt2 * BASE2 + txt[i]) % MOD2;
    }

    for(int i = 0; i <= n-m; ++i) {
        if(hPat1 == hTxt1 && hPat2 == hTxt2) {
            printf("Match found at index: %d\n", i);
        }

        if(i < n-m) {
            hTxt1 = ((hTxt1 - txt[i]*h1) * BASE1 + txt[i+m]) % MOD1;
            hTxt2 = ((hTxt2 - txt[i]*h2) * BASE2 + txt[i+m]) % MOD2;

            if(hTxt1 < 0) hTxt1 += MOD1;
            if(hTxt2 < 0) hTxt2 += MOD2;
        }
    }
}

int main()
{
    string txt, pat;

    txt = string("abc aabcaa abc");
    pat = string("abc");

    search_by_hashing(txt, pat);

    return 0;
}

/*
Output:

Match found at index: 0
Match found at index: 5
Match found at index: 11
*/
