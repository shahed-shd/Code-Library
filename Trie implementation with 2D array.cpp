// Trie data structure implementation with 2D array.
// Language : C++11

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 10000 + 3;
const int ALPHABET = 26;            // 'a' to 'z'
const int ROOT = 0;

int nxt[MAXN][ALPHABET];
int info[MAXN];                     // It also can be a struct which binds several data.
int trieSize;

inline void reset_row(int v)
{
    //for(int i = 0; i < ALPHABET; ++i) nxt[v][i] = 0;
    fill(&nxt[v][0], &nxt[v][0]+ALPHABET, 0);
}

void trie_insert(string &str)
{
    int v = ROOT;

    for(auto &x : str) {
        int &rf = nxt[v][x-'a'];
        if(rf == 0) {
            rf = ++trieSize;
            reset_row(trieSize);
        }
        v = rf;
    }

    ++info[v];                      // Update info.
}

bool trie_search(string &str)
{
    int v = ROOT;

    for(auto &x : str) {
        int &rf = nxt[v][x-'a'];
        if(rf == 0) {
            return false;           // Full str isn't found.
        }
        v = rf;
    }

    return (info[v] > 0);
}

int main()
{
    fill(info, info+MAXN, 0);       // Reset info.
    reset_row(ROOT);                // Reset root row.

    string keys[9] = {"a", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    string output[2] = {"Not Found", "Found"};

    for(int i = 0; i < 9; ++i) trie_insert(keys[i]);

    string qry = "a";
    cout << output[trie_search(qry)] << '\n';

    qry = "brown";
    cout << output[trie_search(qry)] << '\n';

    qry = "brwn";
    cout << output[trie_search(qry)] << '\n';

    qry = "white";
    cout << output[trie_search(qry)] << '\n';

    return 0;
}

/*
Output:

Found
Found
Not Found
Not Found

*/
