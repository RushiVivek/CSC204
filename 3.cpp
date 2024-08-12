#include <iostream>

using namespace std;

struct dll{
	int data;
	struct dll* next;
	struct dll* prev;
};

void insert(dll** a, int i, int j, int x) {
	dll* temp = new dll;
	temp->data = x;
	
	if (a[i] == NULL) {
		temp->next = NULL;
		temp->prev = NULL;
		a[i] = temp;
		return;
	}
	
	if (j == 0) {
		temp->prev = NULL;
		temp->next = a[i];
		if (a[i] != NULL) temp->next->prev = temp;
		a[i] = temp;
		return;
	}
	
	dll* itr = a[i];
	int pos = 0;
	while (pos < j) {
		if (itr->next == NULL) {
			temp->prev = itr;
			temp->next = NULL;
			itr->next = temp;
			return;
		}
		++pos;
		itr = itr->next;
	}
	
	temp->next = itr->next;
	temp->prev = itr;
	temp->next->prev = temp;
	temp->prev->next = temp;
}

void deleteI(dll** a, int i, int j) {
	dll* itr = a[i];
	int pos = 0;
	
	if (a[i] == NULL) {
		cout << "Error performing deletion : ErrorIndexOutOfBounds." << endl;
		return;
	}
	
	if (j == 0) {
		itr->next->prev = NULL;
		a[i] = itr->next;
		free(itr);
		return;
	}
	
	while (pos < j) {
		++pos;
		itr = itr->next;
		if (itr == NULL) {
			cout << "Error performing deletion : ErrorIndexOutOfBounds." << endl;
			return;
		}
	}
	if (itr->next != NULL) {
		itr->next->prev = itr->prev;
	}
	itr->prev->next = itr->next;
	free(itr);
}

void deleteX(dll** a, int i, int x) {
	dll* itr = a[i];
	
	if (a[i] == NULL) {
		cout << "Error performing deletion : ErrorValueNotFound." << endl;
		return;
	}
	
	while (itr->data != x) {
		if (itr->next == NULL) {
			cout << "Error performing deletion : ErrorValueNotFound." << endl;
			return;
		}
		itr = itr->next;
	}
	if (itr->prev != NULL) {
		itr->prev->next = itr->next;
	} else {
		a[i] = itr->next;
	}
	if (itr->next != NULL) {
		itr->next->prev = itr->prev;
	}
	free(itr);
}

void getElementPrev(dll** a, int i, int j, int x) {
	dll* itr;
	dll* its = NULL;
	itr = a[i];
	while (itr != NULL) {
		if (itr->data == x) {
			its = itr;
		}
		itr = itr->next;
	}
	if (its == NULL) {
		cout << "Error retrieving previous element : ErrorValueNotFound." << endl;
		return;
	}
	while (j > 0) {
		if (its->prev == NULL) break;
		its = its->prev;
		--j;
	}
	cout << "Operation getElementPrev(" << i << ", " << j << ", " << x << "): " << its->data << endl;
}

void getElementNext(dll** a, int i, int j, int x) {
	dll* itr;
	dll* its = NULL;
	itr = a[i];
	while (itr != NULL) {
		if (itr->data == x) {
			its = itr;
			break;
		}
		itr = itr->next;
	}
	if (its == NULL) {
		cout << "Error retrieving next element : ErrorValueNotFound." << endl;
		return;
	}
	while (j > 0) {
		if (its->next == NULL) break;
		its = its->next;
		--j;
	}
	cout << "Operation getElementNext(" << i << ", " << j << ", " << x << "): " << its->data << endl;
}

void printList(dll** a, int n) {
	cout << "Doubly Linked List: " << endl;
	for (int i = 0; i < n; ++i) {
		cout << "List " << i << " : ";
		if (a[i] == NULL) {
			cout << endl;
			continue;
		}
		cout << a[i]->data;
		dll* itr = a[i]->next;
		
		while (itr != NULL) {
			cout << " <-> " << itr->data;
			itr = itr->next;
		}
		cout << endl;
	}
}

int main() {
	int n;
	cin >> n;
	dll* a[n];
	
	for (int i = 0; i < n; ++i) {
		a[i] = NULL;
	}
	
	insert(a, 0, 2, 2);
	insert(a, 0, 0, 7);
	insert(a, 0, 0, 8);
	insert(a, 0, 0, 9);
	
	deleteI(a, 0, 4);
	
	deleteX(a, 0, 5);
	
	printList(a, n);
	
	getElementPrev(a, 0, 2, 2);
	getElementNext(a, 0, 1, 8);
	
	return 0;
}
