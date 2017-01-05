// Hopcroft-Karp algorithm - maximum bipartite matching.
// Complexity   :   O(sqrt(V)*E)

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 500 + 3;
const int INF = INT_MAX;
const int NIL = 0;

vector<vector<int> > adjList;
int U, V, pairU[MAXN], pairV[MAXN], dist[MAXN];

bool bfs()
{
    queue<int> q;

    for(int u = 1; u <= U; ++u) {
        if(pairU[u] == NIL) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }

    dist[NIL] = INF;

    while(!q.empty()) {
        int u = q.front(); q.pop();

        if(dist[u] < dist[NIL]) {
            for(auto& v : adjList[u]) {
                if(dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }

    return (dist[NIL] != INF);
}

bool dfs(int u)
{
    if(u == NIL) return true;

    for(auto& v : adjList[u]) {
        if(dist[pairV[v]] == dist[u]+1 && dfs(pairV[v])) {
            pairV[v] = u;
            pairU[u] = v;
            return true;
        }
    }

    dist[u] = INF;
    return false;
}

int hopcroft_karp()
{
    fill(pairU+1, pairU+U+1, NIL);
    fill(pairV+1, pairV+V+1, NIL);

    int matching = 0;

    while(bfs()) {
        for(int u = 1; u <= U; ++u)
            if(pairU[u] == NIL && dfs(u))
                ++matching;
    }

    return matching;
}

int main()
{
    U = 4;                  // Number of vertices on left side.
    V = 4;                  // Number of vertices on right side.
    adjList.resize(U+1);    // Adjacency list to store the bipartite graph

    adjList[1].push_back(2);
    adjList[1].push_back(3);
    adjList[2].push_back(1);
    adjList[3].push_back(2);
    adjList[4].push_back(2);
    adjList[4].push_back(4);

    printf("Maximum matching: %d\n", hopcroft_karp());

    return 0;
}
