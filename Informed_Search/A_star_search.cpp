#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vp vector<pair<ll, ll>>
#define vc vector<char>
#define ump2 unordered_map<char, ll>
#define faster ios::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

void aStarSearch(unordered_map<char, vp> &adj,
                 ump2 &heuristic,
                 char start,
                 char goal,
                 set<char> &nodes)
{
    ump2 gCost;
    unordered_map<char, char> parent;
    set<char> visited;

    for (char node : nodes)
        gCost[node] = INF;

    gCost[start] = 0;

    priority_queue<vector<ll>, vector<vector<ll>>, greater<>> pq;

    // {fCost, gCost, currentNode, parentNode}
    pq.push({heuristic[start], 0, (ll)start, -1});

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        char u = (char)current[2];
        char par = (char)current[3];

        if (visited.count(u))
            continue;

        visited.insert(u);
        parent[u] = par;

        if (u == goal)
            break;

        for (auto edge : adj[u])
        {
            ll cost = edge.first;
            char v = (char)edge.second;

            if (visited.count(v))
                continue;

            ll newCost = gCost[u] + cost;

            if (newCost < gCost[v])
            {
                gCost[v] = newCost;
                ll fCost = newCost + heuristic[v];

                pq.push({fCost, newCost, (ll)v, (ll)u});
            }
        }
    }

    if (!visited.count(goal))
    {
        cout << "Not Reachable\n";
        return;
    }

    vc path;

    for (char cur = goal; cur != start; cur = parent[cur])
        path.push_back(cur);

    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "Shortest Path: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << "\nTotal Cost: " << gCost[goal] << endl;
}

int main()
{
    faster;

    ll n, m;

    cin >> n >> m;

    unordered_map<char, vp> adj;
    set<char> nodes;

    for (int i = 0; i < m; i++)
    {
        char u, v;
        ll w;

        cin >> u >> v >> w;

        adj[u].push_back({w, v});
        adj[v].push_back({w, u});

        nodes.insert(u);
        nodes.insert(v);
    }

    ump2 heuristic;

    for (int i = 0; i < nodes.size(); i++)
    {
        char city;
        ll value;

        cin >> city >> value;

        heuristic[city] = value;
    }

    char start, goal;

    cin >> start >> goal;

    aStarSearch(adj, heuristic, start, goal, nodes);
}