#include <bits/stdc++.h>
using namespace std;


class Graph
{
	int V; 
	list<int> *adj; 
	void bridgeUtil(int v, bool visited[], int discovery[], int low[],
					int parent);
    
public:
	Graph(int V); 
	void addEdge(int v, int w); 
	void bridge(); 
    int hasBridge;
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V + 1];
}


void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}


void Graph::bridgeUtil(int u, bool visited[], int discovery[],
								int low[], int parent)
{
	static int time = 0;
	visited[u] = true;
	discovery[u] = low[u] = ++time;

	for (auto v: adj[u])
	{

		if (!visited[v])
		{
			bridgeUtil(v, visited, discovery, low, u);

			low[u] = min(low[u], low[v]);
			if (low[v] > discovery[u]){
                hasBridge = 1;
                cout << u <<" " << v << endl;
            }
		}
		else if (v != parent)
			low[u] = min(low[u], discovery[v]);
	}
}

void Graph::bridge()
{
    bool visited[V + 1];
	int discovery[V + 1];
	int low[V];
	int parent = -1;

	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (!visited[i])
			bridgeUtil(i, visited, discovery, low, parent);
}


int main()
{
	int V,E;
    cin >> V >> E;
    Graph g(V);
    while(E--){
        int node1,node2;
        cin>> node1>> node2;
        g.addEdge(node1,node2);
    }
    
    g.bridge();

    if(g.hasBridge != 1){
        cout<<"\nNo Bridges\n\n";
    }
    
	return 0;
}