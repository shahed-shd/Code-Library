// Persistent segment tree implementation with array (not pointer).

#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 10 + 3;

struct Node {
    int sum;                    // To store sum of the elements in node.
    int leftId, rightId;        // ID to left and right children.

    Node(int s = 0, int l = -1, int r = -1) {
        sum = s, leftId = l, rightId = r;
    }
};

int arr[MAXN];                  // Input array.

int treeSize = 0;
vector<int> roots;              // Root IDs for all versions.
vector<Node> tree;

void build(int nodeId, int s, int t)            // To construct version-0.
{
    if(s == t) {
        tree[nodeId].sum = arr[s];
        return;
    }

    int left, right, mid = (s + t) >> 1;
    tree.push_back(Node()); tree.push_back(Node());

    tree[nodeId].leftId = left = treeSize++;
    tree[nodeId].rightId = right = treeSize++;

    build(left, s, mid);
    build(right, mid+1, t);

    tree[nodeId].sum = tree[left].sum + tree[right].sum;
}

void upgrade(int prevNodeId, int currNodeId, int s, int t, int idx, int val)    // Upgrades to new version.
{
    if(s == t) {        // s == t == idx
        tree[currNodeId].sum = val;
        return;
    }

    int left, right, mid = (s + t) >> 1;
    tree.push_back(Node());

    if(idx <= mid) {
        tree[currNodeId].rightId = right = tree[prevNodeId].rightId;    // Link to right child of previous version.
        tree[currNodeId].leftId = left = treeSize++;

        upgrade(tree[prevNodeId].leftId, left, s, mid, idx, val);
    }
    else {
        tree[currNodeId].leftId = left = tree[prevNodeId].leftId;       // Link to left child of previous version.
        tree[currNodeId].rightId = right = treeSize++;

        upgrade(tree[prevNodeId].rightId, right, mid+1, t, idx, val);
    }

    tree[currNodeId].sum = tree[left].sum + tree[right].sum;
}

int query(int nodeId, int s, int t, int rs, int rt)
{
    if(t < rs || rt < s) return 0;
    if(rs <= s && t <= rt) return tree[nodeId].sum;

    int mid = (s + t) >> 1;

    int q1 = query(tree[nodeId].leftId, s, mid, rs, rt);
    int q2 = query(tree[nodeId].rightId, mid+1, t, rs, rt);

    return q1 + q2;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; ++i) scanf("%d", arr+i);

    tree.push_back(Node());
    roots.push_back(0);
    build(treeSize++, 1, n);


    int updt, idx, val;
    scanf("%d", &updt);

    while(updt--) {
        scanf("%d %d", &idx, &val);

        tree.push_back(Node());
        roots.push_back(treeSize);
        upgrade(roots[roots.size()-2], treeSize++, 1, n, idx,  val);
    }

    int qry, version, l, r;
    scanf("%d", &qry);

    while(qry--) {
        scanf("%d %d %d", &version, &l, &r);

        int res = query(roots[version], 1, n, l, r);
        printf("In version %d, query(%2d, %2d) : %d\n", version, l, r, res);
    }

    return 0;
}

/*
Problem:
Given an array and different point update operations.
Considering each point operation to create a new version of the array, we need to answer the queries of type
v l r : output the sum of elements in range l to r just after the v-th update.

Input:
10
1 2 3 4 5 6 7 8 9 10

3
2 4
5 25
10 123

4
0 1 10
1 1 2
2 4 8
3 1 10

Output:
In version 0, query( 1, 10) : 55
In version 1, query( 1,  2) : 5
In version 2, query( 4,  8) : 50
In version 3, query( 1, 10) : 190

*/
