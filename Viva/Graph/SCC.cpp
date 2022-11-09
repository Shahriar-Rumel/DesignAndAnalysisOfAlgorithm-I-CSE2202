#include <bits/stdc++.h>
using namespace std;

/*  Kosharaju's Algorithm
    1. Order the vertices in decreasing order of finish times in DFS or simply get the topological sort 
    2. Reverse all edges
    3. Do DFS of the reversal graph in the order obtained in step 1. For every vertex, print all reachable vertices
       as one strongly connected component
*/
class Graph{
    int V;
    list<int>*adj;
    void topologicalSort(int s,vector<bool>&visited,stack<int>&st,int low[],int discovery[],int &time,int parent);
    void DFS(int v,vector<bool>&visited);

    public:
    Graph(int V);
    void printSCC();
    void addEdge(int a,int b);
    Graph getTranspose();

};

Graph::Graph(int v){
    this->V = v;
    adj = new list<int>[V];
}

void Graph::DFS(int v,vector<bool> &visited){
    
    visited[v]= true;
    cout<<v<<" ";

    for(auto i :adj[v])
        if(!visited[i])
            DFS(i,visited);
}

Graph Graph::getTranspose(){
    Graph g(V);
    for(int v = 0 ; v < V ; v++){
        for(auto i: adj[v])
            g.adj[i].push_back(v);
    }
    return g;
}

void Graph::addEdge(int v,int w){
    adj[v].push_back(w);
}

void Graph::topologicalSort(int v,vector<bool>&visited,stack<int>&st,int low[],int discovery[],int &time,int parent){
    visited[v] = true;
    low[v]= ++time;
    discovery[v]=time;
    for(auto i:adj[v]){
        if(!visited[i]){
            topologicalSort(i,visited,st,low,discovery,time,v);
            low[v]=min(low[v],low[i]);
        }
        if(v != parent){
            // cout<<"Low before Discovery "<< i <<":"<<discovery[i]<<endl;
            low[v]=min(low[v],discovery[i]);
            // cout<<"Low after Discovery "<< v <<":"<<low[v]<<endl;
        }
    }   
    st.push(v);
}

void Graph::printSCC() 
{ 

    // 1. Order the vertices in decreasing order of finish times in DFS or simply get the topological sort 
	stack<int> s; 
    vector<bool>visited(V,false);
    int low[V];
    int discovery[V];
    int time = 0;
    int parent = -1;

	for(int i = 0; i < V; i++) 
		if(visited[i] == false) 
			topologicalSort(i, visited,s, low,discovery,time,parent); 

    //  2. Reverse all edges
	Graph gr = getTranspose(); 


    // 3. Do DFS of the reversal graph in the order obtained in step 1. For every vertex, print all reachable vertices
    //    as one strongly connected component
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	while (s.empty() == false) 
	{ 
		int v = s.top(); 
		s.pop(); 
 
		if (visited[v] == false) 
		{ 
			gr.DFS(v, visited); 
			cout << endl; 
		} 
	} 
    for(int i = 0 ; i < V ; i++){
        cout<<"Low of "<<i<<" :"<<low[i]<<endl;
    }
} 


int main(){

    int V,E;
    cin >> V >> E;
    Graph g(V);
    while(E--){
        int node1,node2;
        cin>> node1>>node2;
        g.addEdge(node1,node2);
    }
    g.printSCC();

}