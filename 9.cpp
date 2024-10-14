#include <bits/stdc++.h>

using namespace std;

struct tNode{
	char data;
	tNode *left, *right;
	
	tNode(char val) {
		data = val;
		left = right = nullptr;
	}
};

struct qNode{
	tNode* data;
	qNode* next;
	
	qNode(tNode* val) {
		data = val;
		next = nullptr;
	}
};

qNode *head, *tail;

tNode* preintobin(const string pre, const string in1) {
	tNode* root = new tNode(pre[0]);
//	cout << ":" << pre[0] << ";";
	
	int i, n = pre.length();
	for (i = 0; i < n; ++i) {
		if (in1[i] == pre[0]) break;
	}
	
	if (i > 0) root->left = preintobin(pre.substr(1, i), in1.substr(0, i));
	if (i < n-1) root->right = preintobin(pre.substr(i+1), in1.substr(i+1));
	
	return root;
}

tNode* postintobin(const string post, const string in2) {
	tNode* root = new tNode(post.back());
	
	int i, n = post.length();
	for (i = 0; i < n; ++i) {
		if (in2[i] == post.back()) break;
	}
	
	if (i > 0) root->left = postintobin(post.substr(0, i), in2.substr(0, i));
	if (i < n-1) root->right = postintobin(post.substr(i, n-i-1), in2.substr(i+1));
	
	return root;
}

void enqueue(tNode* val) {
	if (tail) {
		qNode* temp = new qNode(val);
		tail->next = temp;
		tail = temp;
	} else {
		head = new qNode(val);
		tail = head;
	}
}

tNode* dequeue() {
	if (head) {
		qNode* temp = head;
		head = head->next;
		if (head == nullptr) tail = nullptr;
		tNode* val = temp->data;
		free(temp);
		return val;
	} else {
		cout << "Queue Underflow.\n";
		return nullptr;
	}
}

void printTree(tNode* root) {
	cout << "Tree :\nLevel order: ";
	if (root) {
		head = tail = nullptr;
		enqueue(root);
		while (head) {
			tNode* t = dequeue();
			cout << t->data << " ";
			if (t->left) enqueue(t->left);
			if (t->right) enqueue(t->right);
		}
	}
	cout << "\n";
}


int main() {
	string pre, in1, post, in2;
	cout << "Preorder and inorder to binary tree : \n\n";
	cout << "Enter the preorder: ";
	cin >> pre;
	cout << "Enter the inorder: ";
	cin >> in1;
	
	tNode* root = nullptr;
	root = preintobin(pre, in1);
	
	printTree(root);
	cout << "\n";

	cout << "Postorder and inorder to binary tree : \n\n";
	cout << "Enter the postorder: ";
	cin >> post;
	cout << "Enter the inorder: ";
	cin >> in2;
	
	root = postintobin(post, in2);
	
	printTree(root);	
	
	return 0;
}
