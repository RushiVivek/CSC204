#include <bits/stdc++.h>
using namespace std;

int n, m;

map<int, vector<pair<int, int>>> adjlist;

class Cmp{
public:
	bool operator() (pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
	}
};

priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> change(priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp>& heap, int i, int d) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> ans;
	while (!heap.empty()) {
		pair<int, int> p = heap.top();
		heap.pop();
		if (p.first != i) {
			ans.push(p);
		} else {
			p.second = d;
			ans.push(p);
		}
	}
	return ans;
}

void print(vector<int>& d) {
	cout << "Vertex Distance from Source\n";
	for (int i = 0; i < n; ++i) {
		cout << i << " \t\t " << d[i] << "\n";
	}
}

void dijkstra(int sta) {
	vector<int> dist(n, INT_MAX);
	dist[sta] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> minheap;
	map<int, bool> isinheap;
	
	for (int i = 0; i < n; ++i) {
		minheap.push({i, dist[i]});
		isinheap[i] = 1;
	}
	
	while (!minheap.empty()) {
		int t = minheap.top().first;
		minheap.pop();
		isinheap[t] = 0;
		
		for (auto i : adjlist[t]) {
			if (dist[t] == INT_MAX) continue;
			if (!isinheap[i.first]) continue;
			if (i.second + dist[t] < dist[i.first]) {
				dist[i.first] = dist[t] + i.second;
				minheap = change(minheap, i.first, dist[i.first]);
			}
		}
	}
	print(dist);
}

// 9 14
// 0 1 4
// 0 7 8
// 1 2 8
// 1 7 11
// 2 3 7
// 2 8 2
// 2 5 4
// 3 4 9
// 3 5 14
// 4 5 10
// 5 6 2
// 6 7 1
// 6 8 6
// 7 8 7

int main() {
	cout << "Enter the number of vertices and edges: ";
	cin >> n >> m;
	cout << "Enter the edge and weight\n";
	for (int i = 0; i < m; ++i) {
		cout << ": ";
		int a, b, w;
		cin >> a >> b >> w;
		adjlist[a].push_back({b, w});
		adjlist[b].push_back({a, w});
	}
	
	dijkstra(0);
	
	return 0;
}
