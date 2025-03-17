#include <bits/stdc++.h>
using namespace std;

int n;

vector<int> bellmanFord(vector<pair<pair<int, int>, int>>& edges, int sta, map<int, int>& p) {
    vector<int> d(n, INT_MAX);
    d[sta] = 0;
    p[sta] = -1;

    for (int i = 0; i < n; ++i) {
        for (auto& edge : edges) {
            int u = edge.first.first;
            int v = edge.first.second;
            int w = edge.second;

            if (d[u] != INT_MAX) {
                if (d[v] > d[u] + w) {
                    if (i == n-1) return {-1};
                    p[v] = u;
                    d[v] = d[u] + w;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (d[i] == INT_MAX) p[i] = -1;
    }

    return d;
}

// 5 5
// 1 3 2
// 4 3 -1
// 2 4 1
// 1 2 1
// 0 1 5

int main() {
    int m, sta;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    cout << "Enter the edges (u v w): \n";
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cout << ": ";
        cin >> u >> v >> w;
        edges.push_back({{u, v}, w});
    }

    cout << "Enter the starting vertex: ";
    cin >> sta;

    map<int, int> path;

    vector<int> res = bellmanFord(edges, sta, path);

    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << " is at distance ";
        if (res[i] == INT_MAX) cout << "INF";
        else cout << res[i];
        cout << "\n";
    }

    for (int i = 0; i < n; ++i) {
        if (i == sta) continue;
        if (path[i] == -1) {
            cout << "Vertex " << i << " is unreachable.\n";
            continue;
        }
        cout << "Shortest path from " << sta << " to " << i << " is";
        vector<int> pa;
        int ch = i;
        while (1) {
            if (path[ch] == -1) break;
            pa.push_back(path[ch]);
            ch = path[ch];
        }
        for (int j = pa.size() - 1; j >= 0; --j) {
            cout << " " << pa[j] << " ->";
        }
        cout << " " << i << "\n";
    }

    return 0;
}