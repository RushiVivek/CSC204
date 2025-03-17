#include <bits/stdc++.h>
using namespace std;

class Node{
	public:
		char data;
		int freq;
		Node* left;
		Node* right;
		
		Node(int f = 0) {
			freq = f;
			left = right = nullptr;
		}
};

vector<Node*> nodes;

void calfreq(string txt) {
	map<char, int> freqs;
	
	for (auto i: txt) {
		++freqs[i];
	}
	for (auto i = freqs.begin(); i != freqs.end(); ++i) {
		Node *tmp = new Node(i->second);
		tmp->data = i->first;
		nodes.push_back(tmp);
	}
}

bool cmpNodes(Node* a, Node* b) {
	return a->freq < b->freq;
}

Node* huffman_tree() {
	while (nodes.size() > 1) {
		sort(nodes.begin(), nodes.end(), cmpNodes);
		Node *left = nodes[0];
		Node *right = nodes[1];
		nodes.erase(nodes.begin());
		nodes.erase(nodes.begin());
		
		Node *mix = new Node(left->freq + right->freq);
		mix->left = left;
		mix->right = right;
		
		nodes.push_back(mix);
	}
	return nodes[0];
}

void generate_codes(map<char, string>& codes, Node* root, string curr) {
	if (root == nullptr) return;
	if (root->data) codes[root->data] = curr;
	
	string l = curr, r = curr;
	l += '0';
	r += '1';
	
	generate_codes(codes, root->left, l);
	generate_codes(codes, root->right, r);
}

map<char, string> huffman_encoding(string txt) {
	nodes.clear();
	calfreq(txt);
	Node* root = huffman_tree();
	
	map<char, string> codes;
	generate_codes(codes, root, "");
	return codes;
}

string encode(string txt, map<char, string>& codes) {
	string encoded_txt = "";
	
	for (auto i : txt) {
		encoded_txt += codes[i];
	}
	
	return encoded_txt;
}

string decode(string encoded_txt, map<char, string>& codes) {
	string txt = "";
	map<string, char> de_codes;
	
	for (auto i = codes.begin(); i != codes.end(); ++i) {
		de_codes[i->second] = i->first;
	}
}

int main() {
	string txt = "Cake or pie? I can tell a lot about you by which one you pick. It may seem silly, but cake people and pie people are really different. I know which one I hope you are, but that's not for me to decide. So, what is it? Cake or pie?", encoded_txt = "";
	map<char, string> codes;
	codes = huffman_encoding(txt);

	encoded_txt = encode(txt, codes);
	cout << "Encoded text = " << encoded_txt << "\n";
	double rat = txt.size() * 8;
	rat /= encoded_txt.size();
	cout << "Ratio = " << rat;
	
	return 0;
}
