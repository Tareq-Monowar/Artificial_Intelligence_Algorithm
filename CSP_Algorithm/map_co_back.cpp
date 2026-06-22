#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

// Available colors
vector<string> colors = {"Red", "Green", "Blue"};

// Graph (Adjacency List)
unordered_map<char, vector<char>> graph;

// Stores assigned colors
unordered_map<char, string> assignedColor;

// Stores all nodes
set<char> nodes;

// Check whether assigning a color is valid
bool isSafe(char node, string color)
{
    for (char neighbor : graph[node])
    {
        if (assignedColor.count(neighbor) &&
            assignedColor[neighbor] == color)
        {
            return false;
        }
    }
    return true;
}

// Backtracking function
bool graphColoring()
{
    // Base Case
    if (assignedColor.size() == nodes.size())
        return true;

    // Find first uncolored node
    char currentNode;

    for (char node : nodes)
    {
        if (!assignedColor.count(node))
        {
            currentNode = node;
            break;
        }
    }

    // Try every color
    for (string color : colors)
    {
        if (isSafe(currentNode, color))
        {
            assignedColor[currentNode] = color;

            if (graphColoring())
                return true;

            // Backtrack
            assignedColor.erase(currentNode);
        }
    }

    return false;
}

int main()
{
    int numberOfNodes, numberOfEdges;

    cout << "Enter number of nodes and edges: ";
    cin >> numberOfNodes >> numberOfEdges;

    cout << "Enter edges (Example: A B)\n";

    for (int i = 0; i < numberOfEdges; i++)
    {
        char u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);

        nodes.insert(u);
        nodes.insert(v);
    }

    if (graphColoring())
    {
        cout << "\nValid Coloring Found:\n";

        for (auto x : assignedColor)
        {
            cout << x.first << " -> " << x.second << endl;
        }
    }
    else
    {
        cout << "No valid coloring exists.\n";
    }

    return 0;
}