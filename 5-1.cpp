#include <iostream>

using namespace std;

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

void printQueue(int* qArr, int n) {
	cout << "Queue: " << endl;
	if (front == -1) return;
	int itr = front;
	while (itr != rear) {
		cout << qArr[itr] << " ";
		++itr;
		itr = itr%n;
	}
	cout << qArr[rear] << endl;;
}

int main() {
	int n;
	cout << "Enter the maximum size of the Queue: ";
	cin >> n;
	int *qArr = new int[n];
	front = rear = -1;
	
	string s;
	do {
		cout << "Enter command (enqueue) (dequeue) (*print) (quit): ";
		cin >> s;
		if (s == "enqueue") {
			int k;
			cout << "Enter the number of values to add: ";
			cin >> k;
			cout << "Enter the values to add: ";
			while (k--) {
				int x;
				cin >> x;
				enqueue(qArr, n, x);
			}
		} else if (s == "dequeue") {
			int v = dequeue(qArr, n);
			if (v != -1) {
				cout << "Popped: " << qArr[v] << endl;
			}
		} else if (s == "quit") continue;
		else {
			printQueue(qArr, n);
		}
	} while (s != "quit");
	
	return 0;
}
