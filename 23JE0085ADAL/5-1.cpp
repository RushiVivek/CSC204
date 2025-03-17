#include <bits/stdc++.h>
using namespace std;

int n;

void print(vector<vector<int>>& graph, vector<int>& p) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; i++) {
        cout << p[i] << " - " << i << " \t";
        cout << graph[p[i]][i] << " \n";
	}
}

void prims(vector<vector<int>>& graph) {
	vector<int> p(n), a(n, INT_MAX);
	vector<bool> ch(n, false);
	
	p[0] = -1;
	a[0] = 0;
	
	for (int i = 0; i < n-1; ++i) {
		int x, mi = INT_MAX;
		
		for (int j = 0; j < n; ++j) {
			if (ch[i]) continue;
			if (a[i] < mi) {
				mi = a[i];
				x = i;
			}
		}
		
		ch[x] = true;
		
		for (int j = 0; j < n; ++j) {
			if (graph[x][j] == 0 || ch[j]) continue;
			if (graph[x][j] < a[j]) {
				p[j] = x;
				a[j] = graph[x][j];
			}
		}
	}
	
	print(graph, p);
}

// 5
// 0, 2, 0, 6, 0
// 2, 0, 3, 8, 5
// 0, 3, 0, 0, 7
// 6, 8, 0, 0, 9
// 0, 5, 7, 9, 0

int main() {
	cout << "Enter the number of vertices: ";
	cin >> n;
	
	vector<vector<int>> graph(n, vector<int>(n));
	cout << "Enter the adjacency matrix\n";
	for (int i = 0; i < n; ++i) {
		cout << "Vertex " << i+1 << " : ";
		for (int j = 0; j < n; ++j) {
			cin >> graph[i][j];
		}
	}
	
	prims(graph);
	
	return 0;
}
