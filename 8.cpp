#include <iostream>
using namespace std;

int n, k;

struct node{
	int data;
	node* next;
	
	node(int v) {
		data = v;
		next = nullptr;
	}
};

node* head = nullptr;

void insert(int x) {
	node* itr = head;
	node* temp = new node(x);
	
	if (itr == nullptr) {
		head = temp;
		return;
	}
	
	while (itr->next != nullptr) {
		itr = itr->next;
	}
	itr->next = temp;
}

void print() {
	cout << "List: ";
	node* itr = head;
	if (itr == nullptr) {
		cout << "\n";
		return;
	}
	
	while (1) {
		cout << itr->data << " -> ";
		itr = itr->next;
		if (itr->next == nullptr) {
			cout << itr->data << "\n";
			break;
		}
	}
}

void create() {
	cout << "Enter number of nodes of linked list: ";
	cin >> n;
	
	cout << "Enter the values of nodes of linked list: ";
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		insert(x);
	}
}

void reverse(int k) {
	node *itr = head, *pre = nullptr, *nex = nullptr, *las = nullptr, *sta = head;
	int cnt = 1;
	head = nullptr;
	
	while(1) {
		las = itr;
		cnt = 1;
		while (cnt < k) {
			las = las->next;
			if (las == nullptr) break;
			++cnt;
		}
		if (cnt != k) break;
		if (head == nullptr) head = las;
		else sta->next = las;
		
		sta = itr;
		
		pre = las->next;
		while (cnt--) {
			nex = itr->next;
			itr->next = pre;
			pre = itr;
			itr = nex;
		}
		if (itr == nullptr) break;
	}
}

struct hNode{
	int data;
	hNode* next;
};

void hashIns(hNode** chHash, int val) {
	hNode* t = new hNode;
	t->data = val;
	t->next = nullptr;
	hNode* itr = chHash[val%n];
	if (itr == nullptr) {
		chHash[val%n] = t;
		return;
	}
	while (itr->next != nullptr) {
		itr = itr->next;
	}
	itr->next = t;
}

bool search(hNode** chHash, int val) {
	hNode* itr = chHash[val%n];
	while (itr != nullptr) {
		if (itr->data == val) return true;
		itr = itr->next;
	}
	return false;
}

void delrept() {
	hNode* chHash[n];
	for (int i = 0; i < n; ++i) {
		chHash[i] = nullptr;
	}
	
	if (head == nullptr) return;
	node* itr = head;
	
	hashIns(chHash, head->data);
	
	while (itr->next != nullptr) {
		if (search(chHash, itr->next->data)) {
//			cout << itr->next->data << "\n";
			node* t = itr->next;
			itr->next = t->next;
			free(t);
		} else {
			hashIns(chHash, itr->next->data);
		}
		itr = itr->next;
	}
}

int main() {
	create();
	cout << "Enter value of k: ";
	cin >> k;
	
	cout << "Reversing: \n";
	cout << "	Initial ";
	print();
	reverse(k);
	cout << "	Reversed ";
	print();
	
	cout << "Removing the duplicates: \n";
	cout << "	Initial ";
	reverse(k);
	print();
	delrept();
	cout << "	Final ";
	print();
	
	return 0;
}
