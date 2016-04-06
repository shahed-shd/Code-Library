// Algorithm        : Topological sort.
// Related problem  : UVa 10305 - Ordering Tasks.cpp

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 12;

vector<vector<int> > adjList;

int indegree[MAXN] = {0};
vector<int> solution;

void topoSort()
{
    queue<int> q;

    for(int i = 0; i < MAXN; ++i)
        if(indegree[i] == 0)
            q.push(i);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        solution.push_back(u);

        for(unsigned i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];
            --indegree[v];

            if(indegree[v] == 0) q.push(v);
        }
    }
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

    for(unsigned i = 0; i < adjList.size(); ++i)    // Counting indegree. It can be done while taking input.
        for(unsigned j = 0; j < adjList[i].size(); ++j)
            ++indegree[adjList[i][j]];

    topoSort();

    for(auto& x : solution)
        cout << x << ' ';

    return 0;
}
