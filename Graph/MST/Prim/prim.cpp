// Prims algorithm:
// 1. Add the node with the lowest edge cost to the MST 
// 2. Find the next node which connects the MST with the rest of the graph considering the cost 
// 3. Repeat untill all the nodes are added into the MST

#include<bits/stdc++.h>
using namespace std;

#define ll long long

const ll INF = 1e10 + 7; // Initial Cost of Each Vertex


class Node {
    public:

        ll w;
        ll v;

        Node(){
            w = INF;
            v = 0;
        }

        Node(ll a,ll b){
            w = a;
            v = b;
        }
};

void swap(Node* a,Node* b){

    Node tmp = *a;
    *a = *b;
    *b = tmp;

}

// Heap implementation to extract the minimum

class Heap {

    private:

        Node heap[200005];
        ll count = 0;

    public:
        Heap(){
            count = 0;
        }

        void insert(Node x) {

            heap[count] = x;
            ll current = count;

            while(true){

                if(heap[current/2].w > heap[current].w){

                    swap(&heap[current],&heap[current/2]);
                    current = current/2;
                }
                else
                    break;
            }
            count++;
        }


        Node extract_min(){

            ll i = 0;

            if(count == 0)
                return {-1,-1};

            Node minimum = heap[0];
            count--;
            swap(&heap[0],&heap[count]);


            while(true){
                
                if( (2*i+1) <= count - 1 ){
                    
                    if( heap[i].w > heap[2*i+1].w && heap[i].w > heap[2*i].w ){
                        
                        if( heap[2*i].w < heap[2*i+1].w ){
                            swap(&heap[i] , &heap[2*i]);
                            i = 2*i;
                        }
                        else{
                            swap(&heap[i] , &heap[2*i+1]);
                            i = 2*i+1;
                        }
                    }
                    else if( heap[i].w > heap[2*i+1].w ){
                        swap(&heap[i] , &heap[2*i+1]);
                        i = 2*i+1;
                    }
                    else if( heap[i].w > heap[2*i].w ){
                        swap(&heap[i] , &heap[2*i]);
                        i = 2*i;
                    }
                    else
                        break;
                    
                }
                else if( 2*i <= count-1 ){
                    if( heap[i].w > heap[2*i].w ){
                        swap( &heap[i],&heap[2*i] );
                        i = 2*i;
                    }
                    else
                        break;
                }
                else
                    break;
            }

            return minimum;
        }

        bool isEmpty(){

            if(count == 0)
                return true;
            else
                return false;
        }
};


vector<Node> adj[100005];
ll MST[100005];
ll key[100005];
ll parent[100005];

// Prim's Naive Implementation

void prims_naive(){

    time_t start,stop;
    time(&start);

    FILE* inputFile = fopen("in.txt","r");
    FILE* outputFile = fopen("out.txt","w");

    memset(MST,0,sizeof(MST));
    memset(parent,-1,sizeof(parent));

    for(ll i = 1; i <= 100002; i++){

        key[i] = INF;

    }

    ll vertex,edge,x,y,z,i,j;
    fscanf(inputFile,"%lld %lld",&vertex,&edge);

    for(i = 1; i <= edge; i++){

        fscanf(inputFile,"%lld %lld %lld",&x,&y,&z);

        adj[x].push_back({z,y});
        adj[y].push_back({z,x});

    }

    key[1] = 0;

    for(ll k = 1; k <= vertex; k++){

        ll temp_key = INF;
        ll temp_vertex = 0;
        for(j = 1; j <= vertex; j++){

            if(key[j]<temp_key && MST[j] == 0){

                temp_key = key[j];
                temp_vertex = j;

            }

        }

        MST[temp_vertex] = 1;

        for(i = 0; i < adj[temp_vertex].size(); i++) {

            Node temp_node = adj[temp_vertex][i];

            if(MST[temp_node.v] == 0 && key[temp_node.v] > temp_node.w){

                key[temp_node.v] = temp_node.w;
                parent[temp_node.v] = temp_vertex;

            }
        }
    }

    ll ans = 0;

    for(i = 1; i <= vertex; i++){

        if(MST[i] == 0){
            fprintf(outputFile, "Graph is not connected\n");
            return ;
        }
        else
            ans+=key[i];
    }

    fprintf(outputFile, "Cost of building the MST : %lld\n", ans);

    time(&stop);
    double runtime = double(stop - start);
    fprintf(outputFile, "Time taken to complete the task : %lf\n", runtime);

    fclose(inputFile);
    fclose(outputFile);

}


// Prim's Efficient Implementation

Heap heapImpl;

void prims_efficient() {

    time_t start,stop;
    time(&start);

    FILE* inputFile = fopen("in.txt","r");
    FILE* outputFile = fopen("out.txt","w");

    memset(MST,0,sizeof(MST));
    memset(parent,-1,sizeof(parent));

    for(ll i = 1; i <= 100002 ; i++ ) key[i] = INF;
    
    ll vertex,edge;

    fscanf(inputFile,"%lld %lld",&vertex,&edge);

    ll src,dst,w,i,j;

    for( i = 1; i <= edge ; i++){

        fscanf(inputFile,"%lld %lld %lld",&src,&dst,&w);

        adj[src].push_back({w,dst});
        adj[dst].push_back({w,src});
    }

    key[1] = 0;
    heapImpl.insert({key[1],1});
    MST[1] = 1;

    while(!heapImpl.isEmpty()){

        Node temp = heapImpl.extract_min();
        MST[temp.v] = 1;

        for(ll i = 0; i < adj[temp.v].size(); i++){

            Node a = adj[temp.v][i];

            if( MST[a.v] == 0 && key[a.v] > a.w ){

                key[a.v] = a.w;
                parent[a.v] = temp.v;
                heapImpl.insert(a);

            }
        }

    }

    ll ans = 0;

    for(i = 1; i <= vertex ; i++){

        if( MST[i] == 0 ){

            fprintf(outputFile, "Graph is not connected\n");
            return ;
        }
        ans += key[i];
    }

    fprintf(outputFile, "Cost of building the MST : %lld\n", ans);

    time(&stop);
    double runtime = double(stop - start);

    fprintf(outputFile, "Time taken to complete the task : %lf\n", runtime);

    fclose(inputFile);
    fclose(outputFile);

}

int main() {
   
    // prims_naive();
    prims_efficient();

    return 0;
}