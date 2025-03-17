#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	cout << "Enter n: ";
	cin >> n;
	
	cout << "Enter Array: ";
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	int limit = 0;
	int ans = 0;
	int en = 0;
	
	for (int i = 0; i < n; ++i) {
		if (i + a[i] > limit) limit = a[i] + i;
		
		if (en == i) {
			++ans;
			en = limit;
			if (limit >= n-1) break;
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}
