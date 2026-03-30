#include <vector>
#include <queue>
using namespace std;

class Prims
{
public:
    static int spanningTree(int V, vector<vector<pair<int,int>>> &adj) {

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        vector<bool> visited(V, false);

        int res = 0;

        pq.push({0, 0});

        while(!pq.empty()) {

            auto p = pq.top();
            pq.pop();

            int wt = p.first;
            int u = p.second;

            if(visited[u])
                continue;

            res += wt;
            visited[u] = true;

            for(auto &v : adj[u]) {
                int node = v.first;
                int weight = v.second;

                if(!visited[node]) {
                    pq.push({weight, node});
                }
            }
        }

        return res;
    }
};