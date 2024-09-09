#include <iostream>

using namespace std;

int n, tc1, tc2;

struct hNode{
	int data;
	hNode* next;
};

void insert1(hNode** chHash, int val) {
	hNode* t = new hNode;
	t->data = val;
	t->next = NULL;
	hNode* itr = chHash[val%n];
	if (itr == NULL) {
		chHash[val%n] = t;
		return;
	}
	++tc1;
	while (itr->next != NULL) {
		itr = itr->next;
		++tc1;
	}
	itr->next = t;
}

void delete1(hNode** chHash, int val) {
	hNode* itr = chHash[val%n];
	if (itr == NULL) {
		cout << "Value Not Found!" << endl;
		return;
	}
	if (itr->data == val) {
		chHash[val%n] = itr->next;
		free(itr);
		return;
	}
	while (itr->next != NULL) {
		if (itr->next->data == val) {
			hNode* temp = itr->next;
			itr->next = itr->next->next;
			free(temp);
			return;
		}
		itr = itr->next;
	}
	cout << "Value Not Found!" << endl;
}

bool search1(hNode** chHash, int val) {
	hNode* itr = chHash[val%n];
	while (itr != NULL) {
		if (itr->data == val) return true;
		itr = itr->next;
	}
	return false;
}

void insert2(int* lpHash, int val) {
	int h = val%n;
	while (lpHash[h] >= 0) {
		++tc2;
		h = (h+1)%n;
		if (h == val%n) {
			cout << "Hash table is full!" << endl;
			return;
		}
	}
	lpHash[h] = val;
}

void delete2(int* lpHash, int val) {
	int h = val%n;
	while (lpHash[h] != -1) {
		if (lpHash[h] == val) {
			lpHash[h] = -2;
			return;
		}
		h = (h+1)%n;
		if (h == val%n) break;
	}
	cout << "Value Not Found!" << endl;
}

bool search2(int* lpHash, int val) {
	int h = val%n;
	while (lpHash[h] != -1) {
		if (lpHash[h] == val) return true;
		h = (h+1)%n;
		if (h == val%n) break;
	}
	return false;
}

void printHash(hNode** chHash, int* lpHash) {
	cout << "Hash Table using Chaining: " << endl;
	for (int i = 0; i < n; ++i) {
		cout << "Row " << i << ":";
		if (chHash[i] == NULL) {
			cout << " Empty" << endl;
			continue;
		}
		hNode* itr = chHash[i];
		while (itr != NULL) {
			cout << " " << itr->data;
			itr = itr->next;
		}
		cout << endl;
	}
	cout << "Hash Table using linear probing: " << endl;
	for (int i = 0; i < n; ++i) {
		cout << "Row " << i << ": ";
		if (lpHash[i] < 0) cout << "Empty";
		else cout << lpHash[i];
		cout << endl;
	}
}

int main() {
	cout << "Enter the size of hash table: ";
	cin >> n;
	
	tc1 = tc2 = 0;
	hNode* chHash[n];
	int lpHash[n];
	
	for (int i = 0; i < n; ++i) {
		chHash[i] = NULL;
		lpHash[i] = -1;
	}

	string inp;
	while (1) {
		cout << "\nEnter command (ins = insert) (del = delete) (s = search) (*print) (col = collisions) (q = quit): ";
		cin >> inp;
		if (inp == "quit" || inp == "q") break;
		else if (inp == "ins" || inp == "insert") {
			cout << "Enter which Hash table to insert to (*1) (2): ";
			int ta;
			cin >> ta;
			
			cout << "Enter number of values to insert: ";
			int x, num;
			cin >> num;
			cout << "Enter the values to insert: ";
			while (num--) {
				cin >> x;
				
				if (ta != 2) insert1(chHash, x);
				else insert2(lpHash, x);
			}
		} else if (inp == "del" || inp == "delete") {
			cout << "Enter which Hash table to delete from (*1) (2): ";
			int ta;
			cin >> ta;
			
			cout << "Enter the value to delete: ";
			int x;
			cin >> x;
			
			if (ta != 2) delete1(chHash, x);
			else delete2(lpHash, x);
		} else if (inp == "search" || inp == "s") {
			cout << "Enter which Hash table to search in (*1) (2): ";
			int ta;
			cin >> ta;
			
			cout << "Enter the value to search for: ";
			int x;
			cin >> x;
			bool fnd;
			
			if (ta != 2) fnd = search1(chHash, x);
			else fnd = search2(lpHash, x);
			
			if (fnd) cout << "Value is present in the Hash table.\n";
			else cout << "Value is not present in the Hash table.\n";
		} else if (inp == "col" || inp == "collisions") {
			cout << "The number of collisions occured in Hash table 1 = " << tc1 << ".\n";
			cout << "The number of collisions occured in Hash table 2 = " << tc2 << ".\n";
		} else printHash(chHash, lpHash);
	}
}
