#include <bits/stdc++.h>
using namespace std;

// Kahn's algorithm for BFS based Topological Sort
// 1. Store Indegree of every Vertex
// 2. Create a Queue , q
// 3. Add all 0 indegree vertices into the q;
// 4. While q is not empty
//      a. pop front node u of q
//      b. print the vertex
//      c. for every adjacent vertex of u
//           i.  Reduce indegree of vertex by 1
//           ii. If indegree becomes 0 add it to the q.

//Implementation

//Adding Edge
void addEdge(vector<int> adj[],int u , int v){
    adj[u].push_back(v);
}

void TopologicalSort(vector<int>adj[],int V){

    // 1. Store Indegree of every Vertex
    vector<int>indegree(V,0);
    for(int currentVertex = 0; currentVertex < V ;currentVertex++){  //for all vertex of V
        for(int adjacentOfCurrentVertex : adj[currentVertex]){
            indegree[adjacentOfCurrentVertex]++;
        }
    }
    // 2. Create a Queue , q
    queue<int>q;

    // 3. Add all 0 indegree vertices into the q;
    for(int i = 0 ; i < V ; i++){
        if(indegree[i]==0)
            q.push(i);
    }

    // 4. While q is not empty
    while(!q.empty()){

        //a. pop front node u of q
        int u = q.front();
        q.pop();

        //b. print the vertex
        cout<<u<<" ";

        //c. for every adjacent vertex of u
        for(int x : adj[u]){
             //i.  Reduce indegree of vertex by 1
             indegree[x]--;
            //ii. If indegree becomes 0 add it to the q.
            if(indegree[x] == 0)
                q.push(x);
        }   
    }
}

int main(){
    //IO
    int Vertices,Edges;
    cin>>Vertices>>Edges;
    vector<int>adjacencyList[Vertices];

    while(Edges--){
        int firstNode,secondNode;
        cin>>firstNode>>secondNode;
        addEdge(adjacencyList,firstNode,secondNode);
    }

    //Topological Sort Call
    TopologicalSort(adjacencyList,Vertices);

}

