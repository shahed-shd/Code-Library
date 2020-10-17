import java.util.Arrays;

public class BinIdxTreeDemo {
    public static void main(final String[] args) {
        int n = 10;
        BinIdxTree bit = new BinIdxTree(n);

        int from = 5;
        int to = 8;
        long value = 100;

        bit.update(from, value);
        bit.update(to + 1, -value);

        for (int i = 1; i <= n; ++i) {
            if (from <= i && i <= to) {
                assert bit.query(i) == value;
            } else {
                assert bit.query(i) == 0;
            }
        }
    }
}

class BinIdxTree {
    long[] tree;
    int sz; // 1 based indexed fenwick tree

    BinIdxTree(int n) {
        sz = n;
        tree = new long[n + 3];
        Arrays.fill(tree, 0L);
    }

    int offset(int x) {
        return x & (-x);
    }

    void update(int idx, long val) {
        while (idx <= sz) {
            tree[idx] += val;
            idx += offset(idx);
        }
    }

    long query(int idx) {
        long sum = 0;

        while (idx > 0) {
            sum += tree[idx];
            idx -= offset(idx);
        }

        return sum;
    }
}