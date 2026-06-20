#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

void dijkstra(vector<vector<pair<long long, long long>>>& graph,
              vector<long long>& distance,
              vector<long long>& parent,
              int source)
{
    priority_queue<
        pair<long long, long long>,
        vector<pair<long long, long long>>,
        greater<pair<long long, long long>>
    > pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto current = pq.top();
        pq.pop();

        long long currentDistance = current.first;
        long long currentNode = current.second;

        if (currentDistance > distance[currentNode])
            continue;

        for (auto edge : graph[currentNode])
        {
            long long nextNode = edge.first;
            long long weight = edge.second;

            long long newDistance = distance[currentNode] + weight;

            if (newDistance < distance[nextNode])
            {
                distance[nextNode] = newDistance;
                parent[nextNode] = currentNode;

                pq.push({newDistance, nextNode});
            }
        }
    }
}

int main()
{
    int numberOfNodes, numberOfEdges;
    cin >> numberOfNodes >> numberOfEdges;

    vector<vector<pair<long long, long long>>> graph(numberOfNodes + 1);

    for (int i = 0; i < numberOfEdges; i++)
    {
        long long u, v, weight;
        cin >> u >> v >> weight;

        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    vector<long long> distance(numberOfNodes + 1, INF);
    vector<long long> parent(numberOfNodes + 1, -1);

    dijkstra(graph, distance, parent, 1);

    if (distance[numberOfNodes] == INF)
    {
        cout << "-1" << endl;
    }
    else
    {
        vector<long long> path;

        for (int node = numberOfNodes; node != -1; node = parent[node])
        {
            path.push_back(node);
        }

        reverse(path.begin(), path.end());

        cout << "Shortest Path: ";

        for (int node : path)
            cout << node << " ";

        cout << endl;

        cout << "Total Distance: " << distance[numberOfNodes] << endl;
    }

    return 0;
}