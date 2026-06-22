#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Recursive DFS Function
bool dfs(unordered_map<int, vector<int>>& graph,
         unordered_set<int>& visited,
         unordered_map<int, int>& parent,
         int current,
         int destination)
{
    visited.insert(current);

    // Destination found
    if (current == destination)
        return true;

    // Visit all neighbors
    for (int neighbor : graph[current])
    {
        if (!visited.count(neighbor))
        {
            parent[neighbor] = current;

            if (dfs(graph, visited, parent, neighbor, destination))
                return true;
        }
    }

    return false;
}

int main()
{
    int numberOfEdges;
    cin >> numberOfEdges;

    unordered_map<int, vector<int>> graph;

    // Input edges
    for (int i = 0; i < numberOfEdges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);

        // For an undirected graph, uncomment the next line:
        // graph[v].push_back(u);
    }

    int source, destination;
    cin >> source >> destination;

    unordered_set<int> visited;
    unordered_map<int, int> parent;

    bool found = dfs(graph, visited, parent, source, destination);

    if (!found)
    {
        cout << "Not reachable." << endl;
    }
    else
    {
        vector<int> path;

        int current = destination;

        while (current != source)
        {
            path.push_back(current);
            current = parent[current];
        }

        path.push_back(source);

        reverse(path.begin(), path.end());

        cout << "DFS Path: ";

        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];

            if (i + 1 < path.size())
                cout << " -> ";
        }

        cout << endl;
    }

    return 0;
}