#include <iostream>
using namespace std;

void sorta(int* a, int len, int g) {
	
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < len; ++j) {
			if (g == 0) {
				if (a[i] > a[j]) {
					a[i] ^= a[j];
					a[j] ^= a[i];
					a[i] ^= a[j];
				}
			} else {
				if (a[i] < a[j]) {
					a[i] ^= a[j];
					a[j] ^= a[i];
					a[i] ^= a[j];
				}
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	int arr[n][m];
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> arr[i][j];
		}
	}
	
	for (int i = 0; i < n; ++i) {
		sorta(arr[i], m, i%2);
	}
	
	cout << "Sorted Array: \n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}
