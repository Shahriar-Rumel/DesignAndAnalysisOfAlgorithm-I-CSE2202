#include <bits/stdc++.h>
using namespace std;

/*  DFS Based Topological Sort to Detect Cycle

    In Topological Sort, the idea is to visit the parent node 
    followed by the child node. If the given graph contains a cycle, 
    then there is at least one node which is a parent as well as a child so this
    will break Topological Order. Therefore, after the topological sort, 
    check for every directed edge whether it follows the order or not.

    Algorithm
    1.Create an empty stack
    2.For every vertex u,
        if u is not visited
            DFS(u,stack)
    4. Create a map to store key value pair
    5.Create a variable to store initial index

    5.While (stack is not empty)
        a. pop an item from stack
        b. Increment the index and store it as the value correponding to the item as key into the map
    6.For every vertex u in V
        a. For every vertex x in u
            i.if position of parent is less than child vertex
                return cycle exist;
    7 . return cycle doesn't exist


    Modified DFS
    DFS(u,st)
    1. Mark u as visited
    2. For every adjacent v of u
        if(v is not visited)
            DFS(v,st)
    3.Push u to st
*/

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

bool TopologicalSortDFS(vector<int>adj[],int V,vector<bool>&visited){
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

    //  4. Create a map to store key value pair
    map<int,int> order;

    // 5.Create a variable to store initial index
    int index = 0;

    // 6.While (stack is not empty)
    while(!st.empty()){
        //     a. pop an item from stack
        int item = st.top();
        st.pop();
         //     b.  Store it as the value correponding to the item as key into the map and increment the index 
        order[item]= index++;
       
    }

    // 4.For every vertex u in V
    for(int u = 0 ; u< V; u++ ){
        //a. For every vertex x in u
        for(int x : adj[u])
            //i.if position of parent is less than child vertex
            if(order[x] > order[u])
            //return cycle exist;
            return true;
    }
    // 5 . return cycle doesn't exist
    return false;
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
    if(TopologicalSortDFS(adjacencyList,Vertices, visited))cout<<"Cycle Exist"<<endl; 
    else cout<<"Cycle Doesn't Exist"<<endl;
}