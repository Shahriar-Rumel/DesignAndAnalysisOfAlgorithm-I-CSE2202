#include <bits/stdc++.h>
using namespace std;

/*  Shortest Path In DAG Using Topological Sort
    1.Initiliaze dist[V]={INF,INF...}
    2.Set the distance of source as 0 , dist[source] = 0
    3. Find the topological Sort
    4. For every vertex u in the topological sort
        a.For every vertex x in u
            i.if dist[x] is less than the dist[u]+weight(u+x)
                dist[x]=dist[u]+wight(u+x)
    5.return or print the dist array

*/

/*  Kahn's algorithm for BFS based Topological Sort
    1. Store Indegree of every Vertex
    2. Create a Queue , q
    3. Add all 0 indegree vertices into the q;
    4. While q is not empty
        a. pop front node u of q
        b. print the vertex
        c. for every adjacent vertex of u
            i.  Reduce indegree of vertex by 1
            ii. If indegree becomes 0 add it to the q.
*/

// Implementation

//Node for stroing weight

struct Node{
    int v;
    int w;
    Node(int v,int w){
        v = v;
        w = w;
    }
};

// Adding Edge
void addEdge(vector<struct Node*> adj[], int u, int v,int w)
{
    Node *vertex = new Node(v,w);
    adj[u].push_back(vertex);
}

vector<int> TopologicalSort(vector<struct Node*> adj[], int V)
{

    // 1. Store Indegree of every Vertex
    vector<int> indegree(V, 0);
    for (int currentVertex = 0; currentVertex < V; currentVertex++)
    { // for all vertex of V
        for (auto adjacentOfCurrentVertex : adj[currentVertex])
        {
            indegree[adjacentOfCurrentVertex->v]++;
        }
    }
    // 2. Create a Queue , q
    queue<int> q;
    vector<int>v;

    // 3. Add all 0 indegree vertices into the q;
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    // 4. While q is not empty
    while (!q.empty())
    {

        // a. pop front node u of q
        int u = q.front();
        q.pop();

        // b. print the vertex
        // cout << u << " ";
        v.push_back(u);

        // c. for every adjacent vertex of u
        for (auto x : adj[u])
        {
            // i.  Reduce indegree of vertex by 1
            indegree[x->v]--;
            // ii. If indegree becomes 0 add it to the q.
            if (indegree[x->v] == 0)
                q.push(x->v);
        }
    }
    return v;
}

int weight(int u , int v){
    return u+v;
}

vector<int> ShortestPathInDAG(vector<struct Node*>adj[],int src,int V){

    // 1.Initiliaze dist[V]={INF,INF...}
    vector<int>dist(V,INT_MAX);

    // 2.Set the distance of source as 0 , dist[source] = 0
    dist[src] = 0;

    // 3. Find the topological Sort
    vector<int> sorted = TopologicalSort(adj, V);

    // 4. For every vertex u in the topological sort
    for(auto u : sorted){
        //     a.For every vertex x in u
        for(auto x:adj[u]){
        //         i.if dist[x] is less than the dist[u]+weight(u+x)
            if(dist[x->v] < dist[u] + weight(dist[u], x->w))
                    dist[x->v]=dist[u]+ weight(dist[u], x->w);
        //             dist[x]=dist[u]+wight(u+x)
        }
    }
    // 5.return or print the dist array
    return dist;
}


int main()
{
    // IO
    int Vertices, Edges;
    cin >> Vertices >> Edges;
    vector<struct Node*> adjacencyList[Vertices];

    while (Edges--)
    {
        int firstNode, secondNode,weight;
        cin >> firstNode >> secondNode >> weight;
        addEdge(adjacencyList, firstNode, secondNode, weight);
    }

    vector<int>ans = ShortestPathInDAG(adjacencyList,0,Vertices);
    for(auto i: ans)cout<<i<<" ";

}
