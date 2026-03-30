#include "Prims.hpp"
#include <iostream>
using namespace std;

int main()
{
    vector<vector<pair<int,int>>> graph;

    graph.push_back({{1,3},{3,7},{4,8}});
    graph.push_back({{0,3},{3,4},{2,1}});
    graph.push_back({{1,1},{3,2}});
    graph.push_back({{0,7},{1,4},{2,2},{4,3}});
    graph.push_back({{0,8},{3,3}});

    int V = 5;

    auto ans = Prims::spanningTree(V, graph);

    cout << ans << endl;
}