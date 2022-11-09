#include <bits/stdc++.h>
using namespace std;

int timer;
vector<vector<int>> adj;
vector<int>start,finish;
vector<int> low;
vector<pair<int,int>> edges;
vector<pair<int,int>> treeEdges;
vector<pair<int,int>> backEdges;

void init(int n){
    timer = 0;
    adj.assign(n+1,{});
    start.assign(n+1,0);
    finish.assign(n+1,0);
    low.assign(n+1,0);
}

void addEdge(int a,int b){
    adj[a].push_back(b);
    // adj[b].push_back(a);
}

void addTreeEdge(int a, int b){
 treeEdges.push_back({a,b});
}

void addBackEdge(int a, int b){
 backEdges.push_back({a,b});
}

void makeGraph(int m){
    for(int i = 0 ; i < m ; i++){
        int node1,node2;
        cin >> node1>> node2;
        edges.push_back({node1,node2});
        addEdge(node1,node2);
    }
}

void DFSRec(int u,int parent){

    start[u] = ++timer;
    low[u] = start[u];
    for(auto x : adj[u]){
        if(!start[x]){
            DFSRec(x,u);
            low[u] = min(low[u],low[x]);
            addTreeEdge(u,x);
        }else if(x != parent) {
            low[u] = min(low[u],start[x]);
        }    
    }
    finish[u] = ++timer;
}

void DFS(int V){

    for(int i = 0 ; i < V ;i++){
        if(!start[i]){
            DFSRec(i,-1);
            cout<<endl;
        }
    }
}

void printTreeEdges(){
    cout<<"Tree Edges are :\n";

    reverse(treeEdges.begin(),treeEdges.end());

    for(auto it : treeEdges){
        cout<<it.first <<" ----> "<< it.second <<endl;
    }
}

void findBackEdges(){
    for(auto it : edges){
        int u = it.first;
        int v = it.second;
        if(start[v] <= start[u] && finish[v] >= finish[u]){
            addBackEdge(u,v);
        }
    }
}

void printBackEdges(){

    if(backEdges.empty()){
      cout<<"There are no backEdges\n";
      return;
    }

    reverse(backEdges.begin(),backEdges.end());

    cout<<"The Back edges are: \n";

    for(auto it : backEdges){
        cout<<it.first <<" ----> "<< it.second <<endl;
    }
}

int main(){

    int V,E;
    cin >> V >> E;
    init(V);
    makeGraph(E);
    DFS(V);
    printTreeEdges();
    findBackEdges();
    printBackEdges();

}