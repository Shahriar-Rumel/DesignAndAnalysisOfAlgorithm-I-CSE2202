#include <bits/stdc++.h>
using namespace std;

int timer;
vector<vector<int>> adj;
vector<int>start,finish;
vector<int> low;
vector<pair<int,int>> edges;
vector<pair<int,int>> treeEdges;
vector<pair<int,int>> backEdges;
vector<bool>isArticulationPoint;

void init(int n){
    timer = 0;
    adj.assign(n+1,{});
    start.assign(n+1,0);
    finish.assign(n+1,0);
    low.assign(n+1,0);
    isArticulationPoint.assign(n+1 , false);
}

void addEdge(int a,int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
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
    int child = 0;
    for(auto x : adj[u]){
        if(!start[x]){
            DFSRec(x,u);
            low[u] = min(low[u],low[x]);
            if(low[x] >= start[u]  && parent != -1) isArticulationPoint[u] = true;
            child++;
            
        }else if(x != parent) {
            low[u] = min(low[u],start[x]);
        }    
    }
    finish[u] = ++timer;
    if(parent  == -1 && child > 1 ) isArticulationPoint[u] = true;
}

void printArticulationPoints(){
    
    cout<<"Articulation Points : ";
    int count = 0;
    for(int i = 0; i < isArticulationPoint.size(); i++){
        if(isArticulationPoint[i]) {
            cout<<i<<" ";
            count++;
        }
    }
    if(!count) cout<<"No articulation Points\n";
}

void DFS(int V){

    for(int i = 0 ; i < V ;i++){
        if(!start[i]){
            DFSRec(i,-1);
            cout<<endl;
        }
    }
}

int main(){

    int V,E;
    cin >> V >> E;
    init(V);
    makeGraph(E);
    DFS(V);
    printArticulationPoints();

}