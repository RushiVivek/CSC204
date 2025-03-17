#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> deg(n);
	for (int i = 0; i < n; i++) cin >> deg[i];

	if (deg[0] > n-1) {
		cout << "Graph is not possible\n";
		return 0;
	}
	for (int i = 0; i < n; i++) {
		if (deg[i] < 0) {
			cout << "Graph is not possible\n";
			return 0;
		}
		for (int j = i+1; j <= i+deg[i]; ++j) {
			--deg[j];
		}
	}
	cout << "Graph is possible\n";

	return 0;
}