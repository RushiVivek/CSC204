#include <bits/stdc++.h>
using namespace std;

int n, m;

int main() {
	cout << "Enter number of vertices and edges: ";
	cin >> n >> m;
	
	cout << "Enter the nodes each edge connects: ";
	vector<vector<int>> adj(n);
	
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	vector<int> col(n, -1);
	col[0] = 0;
	
	vector<bool> used(n, 0);
	
	for (int i = 1; i < n; ++i) {
		for (auto j : adj[i]) {
			if (col[j] != -1) {
				used[col[j]] = 1;
			}
		}
		
		int mex = 0;
		while (mex < n) {
			if (used[mex] == 0) break;
			++mex;
		}
		
		col[i] = mex;
		
		fill(used.begin(), used.end(), 0);
	}
	
	for (int i = 0; i < n; ++i) cout << "Color of vertex " << i << " is: " << col[i] << "\n";
	
	return 0;
}
