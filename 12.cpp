
#include <iostream>
using namespace std;

int n;
int *heap, *A;

void heapify_up(int i) {
	while (i != 0 && heap[(i-1)/2]<heap[i]) {
		swap(heap[i], heap[(i-1)/2]);
		i = (i-1)/2;
	}
}

void heapify_down(int i, int sz) {
	int lar = i, l = 2*i+1, r = 2*i+2;
	if (l < sz && A[l] > A[lar]) {
		lar = l;
	}
	if (r < sz && A[r] > A[lar]) {
		lar = r;
	}
	if (lar != i) {
		swap(A[i], A[lar]);
		heapify_down(lar, sz);
	}
}

void heap_sort() {
	A = new int[n];
	for (int i = 0; i < n; ++i) {
		A[i] = heap[i];
	}
	for (int i = n-1; i > 0; --i) {
		swap(A[0], A[i]);
		heapify_down(0, i);
	}
}

void build_heap() {
	cout << "Enter the size of the array: ";
	cin >> n;
	heap = new int[n];
	cout << "Enter the elements of the array: ";
	for (int i = 0; i < n; ++i) {
		cin >> heap[i];
		heapify_up(i);
	}
}

void print_heap(int *H) {
	cout << "Heap: \n";
	for (int i = 0; i < n; ++i) cout << H[i] << " ";
	cout << "\n";
}

int front, rear;

bool isFull(int n) {
	return ((rear+1)%n == front);
}

void enqueue(int* qArr, int n, int x) {
	if (isFull(n)) {
		cout << "Queue Overflow" << endl;
		return;
	}
	if (front == -1) front = rear = 0;
	else if (front == 0) front = n-1;
	else --front;
	qArr[front] = x;
}

int dequeue(int* qArr, int n) {
	if (front == -1) {
		cout << "Queue Underflow" << endl;
		return -1;
	}
	int val = rear;
	if ((front+1)%n == rear) front = rear = -1;
	else if (rear == 0) rear = n-1;
	else --rear;
	return val;
}

struct tNode{
	int data;
	tNode* left;
	tNode* right;
	tNode* parent;
	
	tNode(int val, tNode* p) {
		data = val;
		parent = p;
		left = right = nullptr;
	}
};

void tree_heapify_up(tNode* node) {
	while (node->parent && node->parent->data < node->data) {
		swap(node->data, node->parent->data);
		node = node->parent;
	}
}

void tree_build_heap() {
	int *qArr = new int[n];
	front = rear = -1;
}

int main() {
	build_heap();
	print_heap(heap);
	heap_sort();
	cout << "Sorted ";
	print_heap(A);
	
	return 0;
}
23JE0085.cpp
Displaying 23JE0085.cpp.
