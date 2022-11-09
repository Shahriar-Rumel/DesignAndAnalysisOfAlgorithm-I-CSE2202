#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

const int INF = 1e9;
int n, tt = 0;
vector<vector<int>> capacity;
vector<vector<int>> adj;

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

int maxflowbfs(int s, int t) {
    int flow = 0;
    vector<int> parent(tt);
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

int main() {
    cin >> n;
    int m; cin >> m;
    vector <int> vv;
    int node = 0, tot = 0;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        tot += x;
        while (x--) {
            vv.push_back(node++);
        }
    }
    adj.assign(n + tot + 10, vector <int>());
    capacity.assign(n + tot + 10, vector <int>(n + tot + 10, 0));
    tt = n + tot + 10;

    vector <int> people;
    for (int i = 0; i < n; ++i) {
        people.push_back(node + i);
        if (i == 0) {
            for(int j = 0 ; j < 5 ; j++){
                adj[vv[j]].push_back(people[i]);
                adj[people[i]].push_back(vv[j]);
                capacity[people[i]][vv[j]] = 1;
            }
            
        } else if (i == 1) {
            int nxt = vv[1];
            adj[nxt].push_back(people[i]);
            adj[people[i]].push_back(nxt);
            capacity[people[i]][nxt] = 1;
            nxt = vv[5];
            adj[nxt].push_back(people[i]);
            adj[people[i]].push_back(nxt);
            capacity[people[i]][nxt] = 1;
        } else if (i == 2) {
            int nxt = vv[0];
            adj[nxt].push_back(people[i]);
            adj[people[i]].push_back(nxt);
            capacity[people[i]][nxt] = 1;
        } else {
            int nxt = vv[1];
            adj[nxt].push_back(people[i]);
            adj[people[i]].push_back(nxt);
            capacity[people[i]][nxt] = 1;
            nxt = vv[5];
            adj[nxt].push_back(people[i]);
            adj[people[i]].push_back(nxt);
            capacity[people[i]][nxt] = 1;
        }
    }
   
    node += n;
    int source = node, dest = node + 1;
    for (int i = 0; i < n; ++i) {
        adj[source].push_back(people[i]);
        adj[people[i]].push_back(source);
        capacity[source][people[i]] = 1;
    }
    for (int v : vv) {
        adj[dest].push_back(v);
        adj[v].push_back(dest);
        capacity[v][dest] = 1;
    }

    auto start = high_resolution_clock::now();
    cout << "Max matching: ";
    cout << maxflowbfs(source, dest) << '\n';
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by max matching: "
         << duration.count() << " microseconds" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Person " << i + 1 << " matched with ";
        for (int v : vv) {
            if (find(adj[people[i]].begin(), adj[people[i]].end(), v) != adj[people[i]].end()) {
                if (capacity[people[i]][v] == 0) {
                    cout << "book " << v + 1 << '\n';
                    break;
                }
            }
        }
    }
}