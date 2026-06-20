#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

// Uniform Cost Search
bool ucs(unordered_map<char, vector<pair<char, long long>>>& graph,
         unordered_map<char, char>& parent,
         unordered_map<char, long long>& cost,
         char source,
         char destination)
{
    priority_queue<
        pair<long long, char>,
        vector<pair<long long, char>>,
        greater<pair<long long, char>>
    > pq;

    pq.push({0, source});
    cost[source] = 0;

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        long long currentCost = current.first;
        char currentNode = current.second;

        if (currentNode == destination)
            return true;

        for (auto edge : graph[currentNode])
        {
            char nextNode = edge.first;
            long long weight = edge.second;

            long long newCost = currentCost + weight;

            if (newCost < cost[nextNode])
            {
                cost[nextNode] = newCost;
                parent[nextNode] = currentNode;

                pq.push({newCost, nextNode});
            }
        }
    }

    return false;
}

int main()
{
    int numberOfEdges;
    cin >> numberOfEdges;

    unordered_map<char, vector<pair<char, long long>>> graph;

    for (int i = 0; i < numberOfEdges; i++)
    {
        char u, v;
        long long weight;

        cin >> u >> v >> weight;

        graph[u].push_back({v, weight});
    }

    unordered_map<char, char> parent;
    unordered_map<char, long long> cost;

    for (auto node : graph)
    {
        cost[node.first] = INF;

        for (auto edge : node.second)
            cost[edge.first] = INF;
    }

    char source, destination;

    cin >> source >> destination;

    bool found = ucs(graph, parent, cost,
                     source, destination);

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

        cout << "UCS Path: ";

        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];

            if (i + 1 < path.size())
                cout << " -> ";
        }

        cout << endl;

        cout << "Total Cost = "
             << cost[destination]
             << endl;
    }

    return 0;
}