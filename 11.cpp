#include <iostream>

using namespace std;

#define MAX 1000

string houses[] = {"Griffindor", "Hufflepuff", "Ravenclaw", "Slytherin"};

struct student{
	int id;
	int marks[3];
};

student arr[MAX];

int n;

int partition(int low, int high) {
	int pivot, up = high, down = low;
	pivot = arr[low].id;
	while (down < up) {
		while (arr[down].id <= pivot && down < up) ++down;
		while (arr[up].id > pivot) --up;
		
		if (down < up) swap(arr[down], arr[up]);
	}
	swap(arr[up], arr[down]);
	return up;
}

void quicksort(int low = 0, int high = n-1) {
	if (low < high) {
		int q = partition(low, high);
		quicksort(low, q-1);
		quicksort(q+1, high);
	}
}

void insertionsort() {
	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0; --j) {
			if (arr[j].id < arr[j-1].id) {
				swap(arr[j], arr[j-1]);
			} else break;
		}
	}
}

int binarysearch(int key) {
	int l = 0, r = n-1, m;
	while (l <= r) {
		m = l + (r-l)/2;
		
		if (arr[m].id == key) {
			return m;
		}
		if (arr[m].id > key) r = m-1;
		else l = m+1;
	}
	return -1;
}

void print() {
	for (int i = 0; i < n; ++i) {
		cout << arr[i].id << " " << houses[(arr[i].id)/10000 - 10];
		for (int j = 0; j < 3; ++j) {
			cout << " " << arr[i].marks[j] << "(00" << j+1 << ")";
		}
		cout << "\n";
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n;
	int it = 0;
	for (int i = 0; i < n; ++i) {
		cin >> arr[it].id;
		cin >> arr[it].marks[0];
		cin >> arr[it].marks[1];
		cin >> arr[it].marks[2];
		
		if (arr[n].id <= 99999 || arr[n].id >= 140000) {
			cout << "Invalid ID\n";
			continue;
		}
		++it;
		insertionsort();
	}
	n = it+1;
	
//	quicksort();
	cout << "Current elements: \n";
	print();
	
	while (1) {
		string inp;
		cout << "Enter command (insert) (print*) (search) (quit): ";
		cin >> inp;
		if (inp == "quit") break;
		else if (inp == "insert") {
			cout << "Enter the data of 3 students to insert: \n";
			for (int i = 0; i < 3; ++i) {
				cout << "Enter id: ";
				cin >> arr[n].id;
				
				if (arr[n].id <= 99999 || arr[n].id >= 140000) {
					cout << "Invalid ID\n";
					continue;
				}
				
				cout << "Enter marks of DADA: ";
				cin >> arr[n].marks[0];
				cout << "Enter marks of charms: ";
				cin >> arr[n].marks[1];
				cout << "Enter marks of potions: ";
				cin >> arr[n].marks[2];
				++n;
			}
			insertionsort();
//			quicksort();
		} else if (inp == "search") {
			int key;
			cout << "Enter id to search for: ";
			cin >> key;
			
			int ind = binarysearch(key);
			if (ind == -1) cout << "Student not found!\n";
			else {
				cout << "Student details: \n" << arr[ind].id << " " << houses[(arr[ind].id)/10000 - 10];
				for (int j = 0; j < 3; ++j) {
					cout << " " << arr[ind].marks[j] << "(00" << j+1 << ")";
				}
				cout << "\n";
			}
		} else {
			cout << "Students list: \n";
			print();
		}
	}
	
	return 0;
}
