#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Dijkstra
{
public:
    static vector<int> shortestPath(vector<vector<pair<int,int>>> &arr)
    {
        int n = arr.size();

        vector<int> dist(n, INT_MAX);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

        dist[0] = 0;
        minHeap.push({0, 0}); // {distance, node}

        while (!minHeap.empty())
        {
            auto p = minHeap.top();
            minHeap.pop();

            int d = p.first;
            int u = p.second;

            // Skip outdated entries
            if (d > dist[u]) continue;

            for (auto i : arr[u])
            {
                int v = i.first;
                int w = i.second;

                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    minHeap.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};