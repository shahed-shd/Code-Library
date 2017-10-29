// Suffix array construction
// Time Complexity : O(n*log(n)*log(n))


#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


struct suff {
    int idx;
    int rnk[2];
};


bool suff_cmp(const suff &a, const suff &b)
{
    if(a.rnk[0] == b.rnk[0])
        return a.rnk[1] < b.rnk[1];

    return a.rnk[0] < b.rnk[0];
}


void build_suff_arr(char str[], int len, int suff_arr[])
{
    suff suffixes[len];

    for(int i = 0; i < len; ++i) {
        suff &sf = suffixes[i];
        sf.idx = i;
        sf.rnk[0] = str[i];
        sf.rnk[1] = (i+1 < len)? str[i+1] : -1;
    }

    sort(suffixes, suffixes+len, suff_cmp);
    int idx_rnk[len];

    for(int k = 4; k < 2*len; k *= 2) {
        int prev_suff_rnk0 = -1;
        int prev_suff_rnk1 = -1;
        int rnk = -1;

        for(int i = 0; i < len; ++i) {
            suff &sf = suffixes[i];

            if(sf.rnk[0] == prev_suff_rnk0 and sf.rnk[1] == prev_suff_rnk1) {
                sf.rnk[0] = rnk;
            }
            else {
                prev_suff_rnk0 = sf.rnk[0];
                prev_suff_rnk1 = sf.rnk[1];
                sf.rnk[0] = ++rnk;
            }

            idx_rnk[sf.idx] = rnk;
        }

        for(int i = 0; i < len; ++i) {
            int next_idx = suffixes[i].idx + k/2;
            suffixes[i].rnk[1] = (next_idx < len)? idx_rnk[next_idx] : -1;
        }

        sort(suffixes, suffixes+len, suff_cmp);
    }

    for(int i = 0; i < len; ++i)
        suff_arr[i] = suffixes[i].idx;
}


int main()
{
    char str[100] = "banana";

    int len = strlen(str);
    int suff_arr[100];

    build_suff_arr(str, len, suff_arr);

    puts("Suffix array:");

    for(int i = 0; i < len; ++i)
        printf("%d ", suff_arr[i]);

    puts("\n\nSorted suffixes:");

    for(int i = 0; i < len; ++i)
        puts(str + suff_arr[i]);

    return 0;
}

/*
Output:

Suffix array:
5 3 1 0 4 2

Sorted suffixes:
a
ana
anana
banana
na
nana

*/
