#include <iostream>

using namespace std;

int n, m, t1, t2;

bool isEmpty(int* sArr, int s) {
	return ((s == 1 && t1 == -1) || (s == 2 && t2 == n-1));
}

bool isFull(int* sArr, int s) {
	return ((s == 1 && t1 == n-1) || (s == 2 && t2 == m+n-1));
}

void pushS(int* sArr, int s, int x) {
	if (isFull(sArr, s)) {
		cout << "Stack " << s << " Overflow" << endl;
		return;
	}
	int t;
	if (s == 1) {
		++t1;
		t = t1;
	} else {
		++t2;
		t = t2;
	}
	sArr[t] = x;
}

int popS(int* sArr, int s) {
	if (isEmpty(sArr, s)) {
		cout << "Stack " << s << " Underflow" << endl;
		return -1;
	}
	int t;
	if (s == 1) {
		t = t1;
		--t1;
	} else {
		t = t2;
		--t2;
	}
	return t;
}

void printS(int* sArr) {
	cout << "Stack 1: ";
	for (int it = t1; it > -1; --it) {
		cout << sArr[it] << " ";
	}
	cout << endl;
	cout << "Stack 2: ";
	for (int it = t2; it > n-1; --it) {
		cout << sArr[it] << " ";
	}
	cout << endl;
}

int main() {
	cout << "Enter the size of Stack 1: ";
	cin >> n;
	cout << "Enter the size of Stack 2: ";
	cin >> m;
	t1 = -1;
	t2 = n-1;
	int *sArr = new int[n+m];
	
	string inp;
	do {
		cout << "Enter which Stack to operate on (*1) (2): ";
		int s;
		cin >> s;
		if (s != 2) s == 1;
		
		cout << "Enter command (push) (pop) (*print) (quit): ";
		cin >> inp;
		if (inp == "push") {
			int k;
			cout << "Enter the number of values to add: ";
			cin >> k;
			cout << "Enter the values to add: ";
			while (k--) {
				int x;
				cin >> x;
				pushS(sArr, s, x);
			}
		} else if (inp == "pop") {
			int v = popS(sArr, s);
			if (v != -1) {
				cout << "Popped: " << sArr[v] << " from Stack " << s << endl;
			}
		} else if (inp == "quit") continue;
		else {
			printS(sArr);
		}
	} while (inp != "quit");
	
	return 0;
}
