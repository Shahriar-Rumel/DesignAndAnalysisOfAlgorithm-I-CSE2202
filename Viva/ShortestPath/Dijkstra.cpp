#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
template <typename T>

class Heap{
    static int const min_size = 1e6 + 10;
    T arr[min_size];
    int size;
    private:
    int parent(int i){
        return i/2;
    }
    int left(int i){
        return 2*i;
    }
    int right(int i){
        return 2*i+1;
    }
    public:
    Heap(){
        size = 1;
    }
    void push(T val){
      arr[size] = val;
      int i = size;
      while(i != 1 && arr[parent(i)] > arr[i]){
        swap(arr[parent(i)], arr[i]);
        i = parent(i);
      }
      size++;
    }
    bool isEmpty(){
        if(size == 1) return 1;
        else return false;
    }
    T top(){
        if(isEmpty()) {
            exit(EXIT_FAILURE);
        }
         return arr[1];
    }
    void pop(){
        if(isEmpty()) return;
        arr[1] = arr[size-1];
        size--;
        heapify(1);
    }
    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int p = parent(i);
        int min_size = i;
        if(l < size && arr[l] < arr[min_size]){
            min_size = l;
        }
        if(r < size && arr[r] < arr[min_size]){
            min_size = r;
        }
        
        if(i != min_size){
            swap(arr[min_size], arr[i]);
            heapify(min_size);
        }

    }
    int size_Heap(){
        return this->size;
    }


};
int const N = 1e3 + 10;
int dist[N];
int parent[N];
vector<pii>g[N];

void dijstra(int s){
    Heap<pii>pq;
    parent[s] = -1;
    pq.push(pii(0,s));
    for(int i = 0; i < N; i++) dist[i] = 1e9+10;
    dist[s] = 0;
    while(!pq.isEmpty()){
        pii u = pq.top();
        pq.pop();
        for(pii i : g[u.second]){
            int node = i.first;
            int distance = i.second; 
            if(dist[node] > dist[u.second] + distance){
                dist[node] = dist[u.second] + distance;
                parent[node] = u.second;
                pq.push(pii(dist[node],node));
            }
        }
    }


}

void pathprint(int s, int desc){
    int p = desc;
    vector<int>path;
    while(p != -1){
        path.push_back(p);
        p = parent[p];
    }
    reverse(path.begin(),path.end());
    for(int i: path) cout<< i <<" ";
    cout<< endl;
    
}
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n,m;
    cin>> n >> m;

    
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(pii(b,c));
        g[b].push_back(pii(a,c));
    }

    dijstra(0);
    for(int i = 0; i < n;i++ ){
        cout<<dist[i]<<" ";
        cout<<"\n";
    }
    int s,d;
    cin >> s >> d;
    pathprint(s,d);

  
}