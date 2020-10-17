#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;

typedef     long long       LL;

class BinIdxTree {
    vector<LL> tree;
    int sz; // 1 based indexed fenwick tree

public:
    BinIdxTree(int n) {
        sz = n;
        tree.assign(n + 1, 0);
    }

    inline int offset(int x) {
        return x & (-x);
    }

    void update(int idx, LL val)
    {
        while (idx <= sz) {
            tree[idx] += val;
            idx += offset(idx);
        }
    }

    LL query(int idx) {
        LL sum = 0;

        while (idx > 0) {
            sum += tree[idx];
            idx -= offset(idx);
        }

        return sum;
    }
};

int main()
{
    int n = 10;
    BinIdxTree bit = BinIdxTree(n);

    int from = 5;
    int to = 8;
    long value = 100;

    bit.update(from, value);
    bit.update(to + 1, -value);

    for (int i = 1; i <= n; ++i) {
        if (from <= i && i <= to) {
            assert(bit.query(i) == value);
        } else {
            assert(bit.query(i) == 0);
        }
    }

    return 0;
}