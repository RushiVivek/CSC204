#include <iostream>

using namespace std;

int front, rear, n;

bool isFull() {
	return ((rear+1)%n == front);
}

void insFront(int* deque, int x) {
	if (isFull()) {
		cout << "Queue Overflow" << endl;
		return;
	}
	if (front == -1) front = rear = 0;
	else if (front == 0) front = n-1;
	else --front;
	deque[front] = x;
}

int delRear(int* deque) {
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

void insRear(int* deque, int x) {
	if (isFull()) {
		cout << "Queue Overflow" << endl;
		return;
	}
	if (front == -1) front = rear = 0;
	else ++rear;
	rear %= n;
	deque[rear] = x;
}

int delFront(int* deque) {
	if (front == -1) {
		cout << "Queue Underflow" << endl;
		return -1;
	}
	int val = front;
	if ((front+1)%n == rear) front = rear = -1;
	else ++front;
	front %= n;
	return val;
}

void printQueue(int* deque) {
	cout << "Queue: " << endl;
	if (front == -1) return;
	int itr = front;
	cout << "Front : ";
	while (itr != rear) {
		cout << deque[itr] << " ";
		++itr;
		itr = itr%n;
	}
	cout << deque[rear] << " : Rear" << endl;
}

void first_negative(int* a, int sz, int k) {
	n = sz-k+1;
	int *deque = new int[n];
	front = rear = -1;
	
	int cnt = 0;
	for (int i = 0; i < sz; ++i) {
		if (cnt == k) {
			while (!isFull() && cnt--) {
				insRear(deque, 0);
			}
			cnt = 0;
		}
		if (a[i] >= 0) ++cnt;
		else {
			while (!isFull() && cnt--) {
				insRear(deque, a[i]);
			}
			insRear(deque, a[i]);
			cnt = 0;
		}
	}
	if (cnt == k) {
		while (!isFull() && cnt--) insRear(deque, 0);
	}
	printQueue(deque);
}

int main() {
	cout << "Enter the length of the Array: ";
	int sz, k;
	cin >> sz;

	int *arr = new int[sz];
	cout << "Enter the elements of the Array: ";
	for (int i = 0; i < sz; ++i) {
		cin >> arr[i];
	}
	cout << "Enter the size of window: ";
	cin >> k;
	
	first_negative(arr, sz, k);
	
//	cout << "Enter the maximum size of the Queue: ";
//	cin >> n;
//	string s;
//	do {
//		cout << "Enter command (push) or (pop) followed by on 1 or 2, (*print) (quit): ";
//		cin >> s;
//		if (s == "push") {
//			int sw;
//			cin >> sw;
//			int k;
//			cout << "Enter the number of values to add: ";
//			cin >> k;
//			cout << "Enter the values to add: ";
//			while (k--) {
//				int x;
//				cin >> x;
//				if (sw == 1) insFront(deque, x);
//				else insRear(deque, x);
//			}
//		} else if (s == "pop") {
//			int sw;
//			cin >> sw;
//			int v;
//			if (sw == 1) v = delFront(deque);
//			else v = delRear(deque);
//			if (v != -1) {
//				cout << "Popped: " << deque[v] << endl;
//			}
//		} else if (s == "quit") continue;
//		else {
//			printQueue(deque);
//		}
//	} while (s != "quit");
	
	return 0;
}
