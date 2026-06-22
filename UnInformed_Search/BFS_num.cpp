#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

void bfs(unordered_map<int, vector<int>>& graph,
         int source,
         int destination)
{
    queue<int> q;
    unordered_set<int> visited;
    unordered_map<int, int> parent;

    q.push(source);
    visited.insert(source);
    parent[source] = -1;   // Source has no parent

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == destination)
            break;

        for (int neighbour : graph[current])
        {
            if (!visited.count(neighbour))
            {
                visited.insert(neighbour);
                parent[neighbour] = current;
                q.push(neighbour);
            }
        }
    }

    if (!parent.count(destination))
    {
        cout << "Destination is not reachable." << endl;
        return;
    }

    vector<int> path;
    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "Shortest Path: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << endl;
}

int main()
{
    int numberOfEdges;

    cout << "Enter number of edges: ";
    cin >> numberOfEdges;

    unordered_map<int, vector<int>> graph;

    cout << "Enter each edge (Source Destination):" << endl;

    for (int i = 0; i < numberOfEdges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);

        // For an undirected graph, uncomment the next line:
        // graph[v].push_back(u);
    }

    int source, destination;

    cout << "Enter source and destination: ";
    cin >> source >> destination;

    bfs(graph, source, destination);

    return 0;
}