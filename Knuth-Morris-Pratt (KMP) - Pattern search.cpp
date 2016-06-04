// Knuth-Morris-Pratt (KMP) algorithm.
// Complexity : O(n+m).

#include<cstdio>
#include<cstring>

void computeLPSArray(char *pat, int m, int *lps);

void KMPSearch(char txt[], char pat[])
{
    int n = strlen(txt), m = strlen(pat);

    int lps[m];
    computeLPSArray(pat, m, lps);

    int i = 0, j = 0;               // i is index for txt[], j is index for pat[].

    while (i < n) {
        if(txt[i] == pat[j]) {
            ++i, ++j;
        }

        if(j == m) {
            printf("Found pattern at index %d\n", i-j);
            j = lps[j-1];
        }
        else if (i < n && txt[i] != pat[j]) {
            if(j != 0)
                j = lps[j-1];
            else
                ++i;
        }
    }
}

void computeLPSArray(char pat[], int m, int lps[])
{
    lps[0] = 0;                     // lps[0] is always 0.
    int i = 1, len = 0;

    while (i < m) {                 // The loop calculates lps[i] for i = 1 to m-1
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        }
        else {                      // (pat[i] != pat[len])
            if (len != 0)
                len = lps[len-1];
            else                    // if (len == 0)
                lps[i++] = 0;
        }
    }
}

int main()
{
    char txt[] = "AABAACAADAABAAABAA";
    char pat[] = "AABA";

    KMPSearch(txt, pat);

    return 0;
}

/*
Output:

Found pattern at index 0
Found pattern at index 9
Found pattern at index 13
*/
