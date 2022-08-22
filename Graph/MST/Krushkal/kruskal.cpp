// Kruskals algorithm
// 1. Sort Edges on non descending order
// 2. Check if adding an edge to the mst creates cycle
//     a. if not then add this edge to the mst and increase the cost
// 3. Repeat 2 until we traverse all V-1 edges
// 4. Return the cost
#include <bits/stdc++.h>

using namespace std;

#define ll long long 

ll visited[100005];
ll parent[100005];
ll ranks[100005];

// For creating Edges 

class Edge {

    public:
        ll w;
        ll src;
        ll dst;
        Edge(){
            w = 0;
            src = 0;
            dst = 0;
        }
        Edge(ll w, ll src, ll dst){
            this->w = w;
            this->src = src;
            this->dst = dst;
        }
};


bool comp(Edge a, Edge b) {
    return a.w < b.w;
}

vector<Edge> MST;
vector<Edge> edges;
vector<ll> adj[100005];

void initialise(ll x){
    for (ll i = 1; i <= x; i++) {
        parent[i] = i;
        ranks[i] = 1;
    }
}


void DFS(ll s, ll *component_count) {
    visited[s] = 1;
    (*component_count)++;

    for (ll i = 0; i < adj[s].size(); i++) {
        ll temp = adj[s][i];
        if (visited[temp] == 0) {
            DFS(temp, component_count);
        }
    }
}

// Kruskal Naive

ll find_naive(ll x) {
    if (parent[x] == x)
        return x;
    
    return find_naive(parent[x]);
    
}


bool union_naive(ll x, ll y){
    
    ll a = find_naive(x);
    ll b = find_naive(y);

    if (a != b){
        parent[b] = a;
        return true;
    }

    return false;
}

void kruskal_naive() {

    time_t start, stop;
    time(&start);

    FILE *inputFile = fopen("in.txt", "r");
    FILE *outputFile = fopen("out.txt", "w");

    ll vertex, edge;

    fscanf(inputFile, "%lld %lld\n", &vertex, &edge);

    initialise(vertex);

    ll src, dst, w, i;


    for (i = 1; i <= edge; i++){
        fscanf(inputFile, "%lld %lld %lld", &src, &dst, &w);
        edges.push_back({w, src, dst});
    }

    sort(edges.begin(), edges.end(), comp);

    for (i = 0; i < edges.size(); i++){
        Edge current = edges[i];

        if (union_naive(current.src, current.dst)){

            MST.push_back(current);
            adj[current.src].push_back(current.dst);
            adj[current.dst].push_back(current.src);
        }
    }

    memset(visited, 0, sizeof(visited));
    ll connected_vertices = 0;
    DFS(1, &connected_vertices);


    if (connected_vertices == vertex){
        ll ans = 0;
        for (i = 0; i < MST.size(); i++) {
            ans += MST[i].w;
        }
         fprintf(outputFile, "Cost of building the MST : %lld\n", ans);
    }
    else
        fprintf(outputFile, "Graph is not connected\n");

    time(&stop);
    double runtime = double(stop - start);

    fprintf(outputFile, "Time taken to complete the task : %lf\n", runtime);

    fclose(inputFile);
    fclose(outputFile);
}

// Kruskal Efficient

ll find_efficient(ll x){

    if (parent[x] == x)
        return x;
    
    return parent[x] = find_efficient(parent[x]);

}

bool union_efficient(ll x, ll y){

    ll a = find_efficient(x);
    ll b = find_efficient(y);

    if (a != b) {
        if (ranks[a] > ranks[b])
            parent[b] = a;
        
        else if (ranks[a] == ranks[b]){
            parent[b] = a;
            ranks[a]++;
        }
        else
            parent[a] = b;

        return true;
    }

    return false;
}

void kruskal_efficient() {

    time_t start, stop;
    time(&start);

    FILE *inputFile = fopen("in.txt", "r");
    FILE *outputFile = fopen("out.txt", "w");

    ll vertex, edge;

    fscanf(inputFile, "%lld %lld\n", &vertex, &edge);

    initialise(vertex);

    ll src, dst, w, i;

    for (i = 1; i <= edge; i++){
        fscanf(inputFile, "%lld %lld %lld", &src, &dst, &w);
        edges.push_back({w, src, dst});
    }

    sort(edges.begin(), edges.end(), comp);

    for (i = 0; i < edges.size(); i++){
        Edge current = edges[i];

        if (union_efficient(current.src, current.dst)){
            MST.push_back(current);
            adj[current.src].push_back(current.dst);
            adj[current.dst].push_back(current.src);
        }
    }

    ll component_count = 0;
    memset(visited, 0, sizeof(visited));
    DFS(1, &component_count);

    if (component_count == vertex){
        ll ans = 0;
        for (i = 0; i < MST.size(); i++){
            ans += MST[i].w;
        }
        fprintf(outputFile, "Cost of building the MST : %lld\n", ans);
    }
    else
        fprintf(outputFile, "Graph is not connected\n");

    time(&stop);
    double runtime = double(stop - start);
    fprintf(outputFile, "Time taken to complete the task : %lf\n", runtime);

    fclose(inputFile);
    fclose(outputFile);
}

int main(){
        kruskal_naive();

        // kruskal_efficient();
}
