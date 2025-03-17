#include <bits/stdc++.h>
using namespace std;

int n, k;

int multistage(map<int, vector<pair<int, int>>>& edges, vector<int>& vpers) {
    vector<int> d(n, INT_MAX);
    d[n-1] = 0;

    for (int i = k-1; i > 0; --i) {
        for (int v = vpers[i-1]; v < vpers[i]; ++v) {
            for (auto& e : edges[v]) {
                if (d[v] > d[e.first] + e.second) {
                    d[v] = d[e.first] + e.second;
                }
            }
        }
    }

    // for (int v = 0; v < n; ++v) {
    //     cout << d[v] << " ";
    // }

    return d[0];
}

// 4
// 1
// 3
// 3
// 1
// 12
// 0 1 1
// 0 2 2
// 0 3 5
// 1 4 4
// 1 5 11
// 2 4 9
// 2 5 5
// 2 6 16
// 3 6 2
// 4 7 18
// 5 7 13
// 6 7 2

int main() {
    int m;
    cout << "Enter the number of stages: ";
    cin >> k;

    cout << "Enter the number of vertices per stage: \n";
    vector<int> vpers(k+1);
    for (int i = 1; i <= k; ++i) {
        cout << "Stage " << i << ": ";
        cin >> vpers[i];
    }

    for (int i = 1; i <= k; ++i) {
        vpers[i] += vpers[i-1];
    }
    n = vpers[k];

    cout << "Enter the number of edges: ";
    cin >> m;
    cout << "Enter the edges (u, v, w): \n";
    map<int, vector<pair<int, int>>> edges;
    for (int i = 0; i < m; ++i) {
        cout << ": ";
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
    }

    int shortest_dist = multistage(edges, vpers);
    cout << "The shortest distance from source stage to destination stage: " << shortest_dist << "\n";
    return 0;
}