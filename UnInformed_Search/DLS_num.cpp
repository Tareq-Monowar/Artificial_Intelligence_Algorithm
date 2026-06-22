#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Depth Limited Search (Recursive)
bool dls(unordered_map<int, vector<int>>& graph,
         unordered_set<int>& visited,
         unordered_map<int, int>& parent,
         int current,
         int destination,
         int limit)
{
    // Destination found
    if (current == destination)
        return true;

    // Depth limit reached
    if (limit == 0)
        return false;

    visited.insert(current);

    // Visit neighbors
    for (int neighbor : graph[current])
    {
        if (!visited.count(neighbor))
        {
            parent[neighbor] = current;

            if (dls(graph, visited, parent,
                    neighbor, destination, limit - 1))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int numberOfEdges;
    cin >> numberOfEdges;

    unordered_map<int, vector<int>> graph;

    // Input graph
    for (int i = 0; i < numberOfEdges; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);

        // For an undirected graph, uncomment the next line:
        // graph[v].push_back(u);
    }

    int source, destination, limit;
    cin >> source >> destination >> limit;

    unordered_set<int> visited;
    unordered_map<int, int> parent;

    bool found = dls(graph, visited, parent,
                     source, destination, limit);

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

        cout << "DLS Path: ";

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