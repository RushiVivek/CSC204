#include <iostream>

using namespace std;

struct sNode{
	int *arr;
	int size;
	int stack_top;
	sNode* prev_list;
	
	sNode(int n, sNode* prev) {
		arr = new int[n];
		size = n;
		stack_top = 0;
		prev_list = prev;
	}
};
sNode* link_top = NULL;

void expand_push(int x) {
	if (link_top->stack_top == link_top->size-1) {
		sNode* t = new sNode(link_top->size, link_top);
		t->arr[0] = x;
		link_top = t;
		return;
	}
	++(link_top->stack_top);
	link_top->arr[link_top->stack_top] = x;
}

int shrink_pop() {
	if (link_top->stack_top == -1) {
		cout << "StackUnderflow!" << endl;
		return 0;
	}
	int val = link_top->arr[link_top->stack_top];
	if (link_top->stack_top == 0) {
		sNode* st = link_top;
		link_top = st->prev_list;
		if (link_top == NULL) {
			link_top = new sNode(st->size, NULL);
			link_top->stack_top = -1;
		}
		free(st);
		return val;
	}
	--(link_top->stack_top);
	return val;
}

int elements() {
	int cnt = 0;
	sNode* st = link_top;
	while (st != NULL) {
		cnt += st->stack_top+1;
		st = st->prev_list;
	}
	return cnt;
}

void print_stack() {
	cout << "Stack: ";
	int arrcnt = 1;
	sNode* st = link_top;
	while (st != NULL) {
		if (st->stack_top == -1) break;
		cout << "\nArray " << arrcnt << ": ";
		for (int i = 0; i <= st->stack_top; ++i) {
			cout << st->arr[i] << " ";
		}
		st = st->prev_list;
		++arrcnt;
	}
	cout << endl;
}

int main() {
	int n;
	cout << "Enter the size of array: ";
	cin >> n;
	link_top = new sNode(n, NULL);
	link_top->stack_top = -1;
	
	string inp;
	cout << "Enter operation to perform (push) (pop) (size) (print) (quit): ";
	cin >> inp;
	
	while (inp != "quit") {
		
		if (inp == "push") {
			cout << "Enter number of elements to push to stack: ";
			int sz;
			cin >> sz;
			cout << "Enter elements to push: ";
			while (sz--) {
				int ele;
				cin >> ele;
				expand_push(ele);
			}
		} else if (inp == "pop") {
			cout << "Popped the number : " << shrink_pop() << endl;
		} else if (inp == "size") {
			cout << "Number of elements in stack = " << elements() << endl;	
		} else if (inp == "print") {
			print_stack();
		}
		cout << "Enter operation to perform (push) (pop) (size) (print) (quit): ";
		cin >> inp;
	}
	
	return 0;
}
