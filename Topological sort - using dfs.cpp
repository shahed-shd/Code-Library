// Algorithm        : Topological sort (using dfs).
// Related problem  : UVa 10305 - Ordering Tasks.cpp

#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 12;

vector<vector<int> > adjList;

bitset<MAXN> visited;
vector<int> solution;

void dfs(int u)
{
    visited[u] = true;

    for(auto& v : adjList[u])
        if(!visited[v])
            dfs(v);

    solution.push_back(u);
}

int main()
{
    adjList.resize(MAXN);

    adjList[0] = {2, 3, 4, 6};
    adjList[1] = {0};
    adjList[2] = {11};
    adjList[5] = {9};
    adjList[6] = {5, 8};
    adjList[7] = {10};
    adjList[8] = {7};

    for(int i = 0; i < MAXN; ++i)
        if(!visited[i]) dfs(i);

    reverse(solution.begin(), solution.end());

    for(auto& x : solution)
        cout << x << ' ';

    return 0;
}
