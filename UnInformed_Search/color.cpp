#include <iostream>
#include <vector>

using namespace std;

// Check if the current color can be assigned
bool isSafe(int node,
            int color,
            vector<vector<int>> &graph,
            vector<int> &colors,
            int n)
{
    for (int i = 0; i < n; i++)
    {
        if (graph[node][i] == 1 && colors[i] == color)
            return false;
    }

    return true;
}

// Backtracking function
bool mapColoring(int node,
                 vector<vector<int>> &graph,
                 vector<int> &colors,
                 int n,
                 int m)
{
    // All nodes are colored
    if (node == n)
        return true;

    // Try every color
    for (int color = 1; color <= m; color++)
    {
        if (isSafe(node, color, graph, colors, n))
        {
            colors[node] = color;

            if (mapColoring(node + 1, graph, colors, n, m))
                return true;

            // Backtrack
            colors[node] = 0;
        }
    }

    return false;
}

int main()
{
    int n, e, m;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the edges (u v):\n";

    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u][v] = 1;
        graph[v][u] = 1; // Undirected graph
    }

    cout << "Enter number of colors: ";
    cin >> m;

    vector<int> colors(n, 0);

    if (mapColoring(0, graph, colors, n, m))
    {
        cout << "\nColor Assignment:\n";

        for (int i = 0; i < n; i++)
        {
            cout << "Node " << i
                 << " ---> Color "
                 << colors[i]
                 << endl;
        }
    }
    else
    {
        cout << "\nNo valid coloring is possible." << endl;
    }

    return 0;
}