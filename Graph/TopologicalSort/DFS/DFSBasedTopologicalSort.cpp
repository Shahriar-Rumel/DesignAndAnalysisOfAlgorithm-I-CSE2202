#include <bits/stdc++.h>
using namespace std;

// Algorithm
// 1.Create an empty stack
// 2.For every vertex u,
//     if u is not visited
//         DFS(u,stack)
// 3.While (stack is not empty)
//     pop an item from stack

// Modified DFS
// DFS(u,st)
// 1. Mark u as visited
// 2. For every adjacent v of u
//     if(v is not visited)
//         DFS(v,st)
// 3.Push u to st

// Implementation
void addEdge(vector<int> adj[], int source, int destination)
{
    adj[source].push_back(destination);
}
void DFS(vector<int> adj[], int source, stack<int> &st, vector<bool> &visited)
{
    visited[source] = true;
    for (int x : adj[source]){
        if (!visited[x])
        {
            DFS(adj, x, st, visited);
        }
    }
    st.push(source);
}

void TopologicalSortDFS(vector<int>adj[],int V,vector<bool>&visited){
    // 1.Create an empty stack
    stack<int> st;
    
    // 2.For every vertex u,
    for(int  u = 0 ; u < V ; u++){
        //     if u is not visited
        if(!visited[u]){
        //         DFS(u,stack)
            DFS(adj,u,st,visited);
        }
    }
    // 3.While (stack is not empty)
    while(!st.empty()){
        //pop an item from stack
        cout<<st.top()<<" ";
        st.pop();
    }
}

int main(){

    int Vertices, Edges;
    cin >> Vertices >> Edges;
    vector<int> adjacencyList[Vertices];
    vector<bool> visited(Vertices,false);
    while (Edges--)
    {
        int firstNode, secondNode;
        cin >> firstNode >> secondNode;
        addEdge(adjacencyList, firstNode, secondNode);
    }

    // Topological Sort Call
    TopologicalSortDFS(adjacencyList,Vertices, visited); 
}