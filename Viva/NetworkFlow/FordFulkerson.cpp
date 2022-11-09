#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

const int INF = 1e9;

int n;
const int N = 1010;
vector<vector<int>> capacity, orig;
vector<vector<int>> adj;
vector <pair <int, int>> st;
vector <bool> vis;
bool found = false;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}


void dfs(int u, int p, int s, int t) {
    if (found) return;
    vis[u] = true;
    if (p != -1) st.push_back({p, u});
    for (int v : adj[u]) {
        if (!vis[v] && capacity[u][v]) {
            dfs(v, u, s, t);
            if (v == t) {
                st.push_back({u, t});
                found = true;
                return;
            }
        }
    }
    if (found) return;
    st.pop_back();
}

int maxflowbfs(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int maxflowdfs(int s, int t) {

    int flow = 0;
    while (!found) {
        st.clear();
        vis.assign(n, false);
        dfs(s, -1, s, t);
        if (found) {
            int new_flow = INF;
            for (auto it: st) {
                int u, v;
                tie(u, v) = it;
                new_flow = min(new_flow, capacity[u][v]);
            }
            flow += new_flow;
            for (auto it: st) {
                int u, v; 
                tie(u, v) = it;
                capacity[u][v] -= new_flow;
                capacity[v][u] += new_flow;
            }
        }
        found ^= 1;
    }
    return flow;
}

int main() {
    cin >> n;
    int m; cin >> m;
    adj.assign(n, vector <int>());
    vis.assign(n, false);
    capacity.assign(n, vector <int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int u, v, c; 
        cin >> u >> v >> c;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] = c;
    }
    orig = capacity;
  
    auto start = high_resolution_clock::now();
    cout << "Max flow with BFS : ";
    cout << maxflowbfs(0, n - 1) << '\n';
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Maxflow BFS : "
         << duration.count() << " microseconds" << endl;
    
    capacity = orig;
    start = high_resolution_clock::now();
    cout << "Max flow with DFS: ";
    cout << maxflowdfs(0, n - 1) << '\n';
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by Maxflow DFS: "
         << duration.count() << " microseconds" << endl;
}