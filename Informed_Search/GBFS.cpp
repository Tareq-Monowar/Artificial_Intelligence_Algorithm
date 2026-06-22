#include <bits/stdc++.h>
using namespace std;

typedef pair<int, char> Edge;

void greedyBestFirstSearch(unordered_map<char, vector<Edge>> &graph,
                           unordered_map<char, int> &heuristic,
                           char start,
                           char goal)
{
    priority_queue<pair<int, char>,
                   vector<pair<int, char>>,
                   greater<pair<int, char>>> pq;

    unordered_map<char, char> parent;
    set<char> visited;

    pq.push({heuristic[start], start});
    parent[start] = '#';

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        char u = current.second;

        if (visited.count(u))
            continue;

        visited.insert(u);

        if (u == goal)
            break;

        for (auto edge : graph[u])
        {
            char v = edge.second;

            if (!visited.count(v))
            {
                pq.push({heuristic[v], v});

                if (parent.find(v) == parent.end())
                    parent[v] = u;
            }
        }
    }

    if (!visited.count(goal))
    {
        cout << "Goal Not Reachable" << endl;
        return;
    }

    vector<char> path;

    for (char cur = goal; cur != '#'; cur = parent[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());

    cout << "Path: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << endl;
}

int main()
{
    int n, m;

    cin >> n >> m;

    unordered_map<char, vector<Edge>> graph;

    for (int i = 0; i < m; i++)
    {
        char u, v;
        int cost;

        cin >> u >> v >> cost;

        graph[u].push_back({cost, v});
        graph[v].push_back({cost, u});
    }

    unordered_map<char, int> heuristic;

    for (int i = 0; i < n; i++)
    {
        char node;
        int h;

        cin >> node >> h;

        heuristic[node] = h;
    }

    char start, goal;

    cin >> start >> goal;

    greedyBestFirstSearch(graph, heuristic, start, goal);

    return 0;
}