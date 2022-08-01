
#ifndef GRAPH_H
#define GRAPH_H
class Graph {
    int V;
    list<int>*adj;

    void topologicalSort(int v,vector<bool> &visited,stack<int> &st);
    void DFS(int v,vector<bool>&visited);
public:
    Graph(int V);
    void addEdge(int v,int w);
    void printSCCs();
    Graph getTranspose();
     

};
Graph::Graph(int V){
    this -> V = V;
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

void Graph::topologicalSort(int v,vector<bool>&visited,stack<int>&st){
    visited[v]=true;
    for(auto i:adj[v])
        if(!visited[i])
            topologicalSort(i,visited,st);
    st.push(v);
}
#endif 
