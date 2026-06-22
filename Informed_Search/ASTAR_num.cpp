#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

// A* Search
void aStarSearch(unordered_map<int, vector<pair<int, int>>> &graph,
                 unordered_map<int, int> &heuristic,
                 int start,
                 int goal,
                 set<int> &nodes)
{
    unordered_map<int, long long> gCost;
    unordered_map<int, int> parent;
    set<int> visited;

    // Initialize all costs to infinity
    for (int node : nodes)
        gCost[node] = INF;

    gCost[start] = 0;

    // {fCost, gCost, currentNode, parentNode}
    priority_queue<
        vector<long long>,
        vector<vector<long long>>,
        greater<>
    > pq;

    pq.push({heuristic[start], 0, start, -1});

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        int currentNode = current[2];
        int parentNode = current[3];

        if (visited.count(currentNode))
            continue;

        visited.insert(currentNode);
        parent[currentNode] = parentNode;

        if (currentNode == goal)
            break;

        for (auto edge : graph[currentNode])
        {
            int weight = edge.first;
            int nextNode = edge.second;

            if (visited.count(nextNode))
                continue;

            long long newCost = gCost[currentNode] + weight;

            if (newCost < gCost[nextNode])
            {
                gCost[nextNode] = newCost;

                long long fCost = newCost + heuristic[nextNode];

                pq.push({fCost,
                         newCost,
                         nextNode,
                         currentNode});
            }
        }
    }

    if (!visited.count(goal))
    {
        cout << "Not Reachable" << endl;
        return;
    }

    vector<int> path;

    for (int node = goal; node != start; node = parent[node])
        path.push_back(node);

    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "Shortest Path: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << endl;

    cout << "Total Cost: "
         << gCost[goal]
         << endl;
}

int main()
{
    int numberOfNodes, numberOfEdges;

    cin >> numberOfNodes >> numberOfEdges;

    unordered_map<int, vector<pair<int, int>>> graph;
    set<int> nodes;

    // Input edges
    for (int i = 0; i < numberOfEdges; i++)
    {
        int u, v, weight;

        cin >> u >> v >> weight;

        graph[u].push_back({weight, v});
        graph[v].push_back({weight, u}); // Undirected

        nodes.insert(u);
        nodes.insert(v);
    }

    unordered_map<int, int> heuristic;

    // Input heuristic values
    for (int i = 0; i < numberOfNodes; i++)
    {
        int node, value;
        cin >> node >> value;

        heuristic[node] = value;
    }

    int start, goal;

    cin >> start >> goal;

    aStarSearch(graph,
                heuristic,
                start,
                goal,
                nodes);

    return 0;
}