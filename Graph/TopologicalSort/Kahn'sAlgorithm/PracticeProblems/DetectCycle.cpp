#include <bits/stdc++.h>
using namespace std;

// Kahn's algorithm for BFS based Topological Sort to Detect Cycle
// 1. Store Indegree of every Vertex
// 2. Create a Queue , q
// 3. Add all 0 indegree vertices into the q;
// 4. Create a count variable
// 5. While q is not empty
//      a. pop front node u of q
//      b. for every adjacent vertex of u
//           i.  Reduce indegree of vertex by 1
//           ii. If indegree becomes 0 add it to the q.
//      c.Incremenet Count
// 6. return whether count is equal to number of verices

// Implementation

void addEdge(vector<int> adj[], int source, int destination)
{
    adj[source].push_back(destination);
}

int DetectCycleUsingTopologicalSort(vector<int> adj[], int V)
{

    // 1. Store Indegree of every Vertex
    vector<int> indegree(V, 0);
    for (int currentVertex; currentVertex < V; currentVertex++)
    {
        for (int adjacentOfCurrentVertex : adj[currentVertex])
            indegree[adjacentOfCurrentVertex]++;
    }

    // 2. Create a Queue , q
    queue<int> q;

    // 3. Add all 0 indegree vertices into the q;
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    // 4. Create a count variable
    int count = 0;

    // 5. While q is not empty
    while (!q.empty())
    {
        // a. pop front node u of q
        int u = q.front();
        q.pop();

        // b. for every adjacent vertex of u
        for (int x : adj[u])
        {
            // i.  Reduce indegree of vertex by 1
            indegree[x]--;

            // ii. If indegree becomes 0 add it to the q.
            if (indegree[x] == 0)
                q.push(x);
        }

        // c.Incremenet Count
        count++;
    }

    // 6. return whether count is equal to number of verices
    return count == V;
}

int main()
{

    int Vertices, Edges;
    cin >> Vertices >> Edges;
    vector<int> adjacencyList[Vertices];

    while (Edges--)
    {
        int firstNode, secondNode;
        cin >> firstNode >> secondNode;
        addEdge(adjacencyList, firstNode, secondNode);
    }

    if (!DetectCycleUsingTopologicalSort(adjacencyList, Vertices))
        cout << "Cycle Detected" << endl;
    else
        cout << "No Cycle" << endl;

    return 0;
}