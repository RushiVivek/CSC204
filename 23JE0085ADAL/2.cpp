#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
//using namespace std::chrono;

int n;
vector<vector<int>> aq, bq, cq;

void genrand() {
	vector<vector<int>> t(n, vector<int>(n));
	aq = bq = cq = t;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			aq[i][j] = rand()%10;
			bq[i][j] = rand()%10;
			cq[i][j] = 0;
		}
	}
}

void norm_mult() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				cq[i][j] += aq[i][k] * bq[k][j];
			}
		}
	}
}

vector<vector<int>> addm(vector<vector<int>> a, vector<vector<int>> b, int spl, int mult = 1) {
	for (int i = 0; i < spl; ++i) {
		for (int j = 0; j < spl; ++j) {
			a[i][j] = a[i][j] + (mult * b[i][j]);
		}
	}
	return a;
}

vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b) {
	int nu = a.size();
	vector<vector<int>> res(nu, vector<int>(nu));
	
	if (nu == 1) {
		res[0][0] = a[0][0]*b[0][0];
		return res;
	}
	
	int spl = nu/2;
	
	vector<vector<int>> a00(spl, vector<int>(spl));
	vector<vector<int>> a01(spl, vector<int>(spl));
	vector<vector<int>> a10(spl, vector<int>(spl));
	vector<vector<int>> a11(spl, vector<int>(spl));
	vector<vector<int>> b00(spl, vector<int>(spl));
	vector<vector<int>> b01(spl, vector<int>(spl));
	vector<vector<int>> b10(spl, vector<int>(spl));
	vector<vector<int>> b11(spl, vector<int>(spl));
	
	for (int i = 0; i < spl; ++i) {
		for (int j = 0; j < spl; ++j) {
			a00[i][j] = a[i][j];
			a01[i][j] = a[i][j + spl];
			a10[i][j] = a[spl + i][j];
			a11[i][j] = a[i + spl][j + spl];
			b00[i][j] = b[i][j];
			b01[i][j] = b[i][j + spl];
			b10[i][j] = b[spl + i][j];
			b11[i][j] = b[i + spl][j + spl];
		}
	}
	
	vector<vector<int>> p(multiply(a00, addm(b01, b11, spl, -1)));
	vector<vector<int>> q(multiply(addm(a00, a01, spl), b11));
	vector<vector<int>> r(multiply(addm(a10, a11, spl), b00));
	vector<vector<int>> s(multiply(a11, addm(b10, b00, spl, -1)));
	vector<vector<int>> t(multiply(addm(a00, a11, spl), addm(b00, b11, spl)));
	vector<vector<int>> u(multiply(addm(a01, a11, spl, -1), addm(b10, b11, spl)));
	vector<vector<int>> v(multiply(addm(a00, a10, spl, -1), addm(b00, b01, spl)));
	
	vector<vector<int>> res_00(addm(addm(addm(t, s, spl), u, spl), q, spl, -1));
	vector<vector<int>> res_01(addm(p, q, spl));
	vector<vector<int>> res_10(addm(r, s, spl));
	vector<vector<int>> res_11(addm(addm(addm(p, t, spl), r, spl, -1), v, spl, -1));
	
	for (int i = 0; i < spl; ++i) {
		for (int j = 0; j < spl; ++j) {
			res[i][j] = res_00[i][j];
			res[i][j+spl] = res_01[i][j];
			res[i+spl][j] = res_10[i][j];
			res[i+spl][j+spl] = res_11[i][j];
		}
	}
	return res;
}

void strassen_mult() {
	cq = multiply(aq, bq);
}

int main() {
	srand(time(0));
	cout << "Enter the value of n: ";
	cin >> n;
	
	genrand();
	
	auto start = chrono::high_resolution_clock::now();
	norm_mult();
	auto stop = chrono::high_resolution_clock::now();
	
	auto dur = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "Normal matrix multiplication time: " << dur.count() << "microseconds\n";
	
	auto start2 = chrono::high_resolution_clock::now();
	strassen_mult();
	auto stop2 = chrono::high_resolution_clock::now();
	
	auto dur2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
	cout << "Strassen's matrix multiplication time: " << dur2.count() << "microseconds\n";
}















