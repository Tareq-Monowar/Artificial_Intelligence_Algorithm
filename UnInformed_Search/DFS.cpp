#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Recursive DFS Function
bool dfs(unordered_map<char, vector<char>>& graph,
         unordered_set<char>& visited,
         unordered_map<char, char>& parent,
         char current,
         char destination)
{
    visited.insert(current);

    // Destination found
    if (current == destination)
        return true;

    // Visit all neighbors
    for (char neighbor : graph[current])
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

    unordered_map<char, vector<char>> graph;

    // Input edges
    for (int i = 0; i < numberOfEdges; i++)
    {
        char u, v;
        cin >> u >> v;

        graph[u].push_back(v);
    }

    char source, destination;
    cin >> source >> destination;

    unordered_set<char> visited;
    unordered_map<char, char> parent;

    bool found = dfs(graph, visited, parent, source, destination);

    if (!found)
    {
        cout << "Not reachable." << endl;
    }
    else
    {
        vector<char> path;

        char current = destination;

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