#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

void bfs(unordered_map<char, vector<char>>& graph,
         char source,
         char destination)
{
    queue<char> q;
    unordered_set<char> visited;
    unordered_map<char, char> parent;

    q.push(source);
    visited.insert(source);
    parent[source] = '\0';   // Source has no parent

    while (!q.empty())
    {
        char current = q.front();
        q.pop();

        if (current == destination)
            break;

        for (char neighbour : graph[current])
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
        cout << "Destination is not reachable.\n";
        return;
    }

    vector<char> path;

    char current = destination;

    while (current != '\0')
    {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "Shortest Path: ";

    for (size_t i = 0; i < path.size(); i++)
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

    unordered_map<char, vector<char>> graph;

    cout << "Enter each edge (Source Destination):\n";

    for (int i = 0; i < numberOfEdges; i++)
    {
        char u, v;
        cin >> u >> v;

        graph[u].push_back(v);
    }

    char source, destination;

    cout << "Enter source and destination: ";
    cin >> source >> destination;

    bfs(graph, source, destination);

    return 0;
}