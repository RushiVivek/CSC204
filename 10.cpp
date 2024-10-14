#include <iostream>
using namespace std;

struct bstNode {
	int data;
	bstNode *right, *left;
	
	bstNode(int val) {
		data = val;
		right = left = nullptr;
	}
};
	
bstNode* insert(bstNode* root, int key) {
	if (root) {
		if (root->data >= key) {
			root->left = insert(root->left, key);
		} else {
			root->right = insert(root->right, key);
		}
		return root;
	} else {
		bstNode* t = new bstNode(key);
		return t;
	}
}

bool search(bstNode* root, int key) {
	if (root == nullptr) return false;
	if (root->data == key) return true;
	else if (root->data > key) return search(root->left, key);
	else return search(root->right, key);
	return false;
}

bstNode* findMin(bstNode* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

bstNode* deleteBst(bstNode* root, int key) {
	if (root == nullptr) return root;
	if (root->data < key) {
		root->right = deleteBst(root->right, key);
		return root;
	}
	if (root->data > key) {
		root->left = deleteBst(root->left, key);
		return root;
	}
	if (root->left == nullptr) {
		bstNode* temp = root->right;
		free(root);
		return temp;
	}
	if (root->right == nullptr) {
		bstNode* temp = root->left;
		free(root);
		return temp;
	}
	bstNode* temp = findMin(root->right);
	root->data = temp->data;
	root->right = deleteBst(root->right, root->data);
	return root;
}

int sumTree(bstNode* root) {
	if (root == nullptr) return 0;
	return root->data + sumTree(root->left) + sumTree(root->right);
}

int sumSubtree(bstNode* root, int key) {
	if (root == nullptr) return 0;
	if (root->data == key) return sumTree(root);
	if (root->data > key) return sumSubtree(root->left, key);
	return sumSubtree(root->right, key);
}

void printPreorder(bstNode* root) {
	if (root == nullptr) return;
	cout << root->data << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}

int main() {
	cout << "Enter the number of elements in the array: ";
	int n;
	cin >> n;
	
	bstNode *root = nullptr;
	
	cout << "Enter the elements of the array: ";
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		root = insert(root, x);
	}
	
	while (1) {
		string inp;
		cout << "Enter command (search) (*print) (sum) (delete) (quit): ";
		cin >> inp;
		if (inp == "search") {
			int x;
			cout << "Enter the key to search for: ";
			cin >> x;
			if (search(root, x)) {
				cout << "Key found!\n";
			} else cout << "Key not found!\n";
		} else if (inp == "delete") {
			int x;
			cout << "Enter the key to delete: ";
			cin >> x;
			root = deleteBst(root, x);
		} else if (inp == "quit") break;
		else if (inp == "sum") {
			int x;
			cout << "Enter root of subtree: ";
			cin >> x;
			cout << "Sum of subtree with " << x << " as root is: " << sumSubtree(root, x) << "\n";
		} else {
			cout << "Preorder: ";
			printPreorder(root);
			cout << "\n";
		}
	}
	
	return 0;
}
