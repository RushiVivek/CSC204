#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

long long n, q, p;

struct Sparce{
	long long row;
	long long col;
	int val;
};

void printArr(int* arr, long long n) {
	for (long long i = 0; i < n; ++i) {
		for (long long j = 0; j < n; ++j) {
			cout << *arr << " ";
			++arr;
		}
		cout << endl;
	}
}

void sumArr(int* a, int* b, int* c, long long n) {
	for (long long i = 0; i < n; ++i) {
		*c = *a + *b;
		++a;++b;++c;
	}
}

void sparceArr(int* arr, struct Sparce* sparr, long long n) {
	for (long long i = 0; i < n; ++i) {
		for (long long j = 0; j < n; ++j) {
			if (*arr != 0) {
				sparr->row = i;
				sparr->col = j;
				sparr->val = *arr;
				++sparr;
			}
			++arr;
		}
	}
}

void printSparce(struct Sparce* sparr, long long p) {
	long long prev = -1;
	for (long long i = 0; i < p; ++i) {
		if (sparr->row != prev) {
			cout << "\nRow " << sparr->row << ":";
			prev = sparr->row;
		}
		cout << " ( " << sparr->val << ", " << sparr->col << ")";
		++sparr;
	}
}

long long sumSparce(struct Sparce* a, struct Sparce* b, struct Sparce* c, long long p) {
	long long base = 0, sz = 0;;
	for (long long i = 0; i < p; ++i) {
        // cout << ":" << base;
		bool ch = false;
		for (long long j = base; j < p; ++j) {
            base = j;
			if (b[j].row > a[i].row) {
				break;
			} else if (b[j].row < a[i].row) {
				c[sz].col = b[j].col;
				c[sz].row = b[j].row;
				c[sz].val = b[j].val;
				++sz;
                if (base == p-1) {
                    ++base;
                }
				continue;
			}
			if (b[j].col > a[i].col) {
				break;
			} else if (b[j].col < a[i].col) {
				c[sz].col = b[j].col;
				c[sz].row = b[j].row;
				c[sz].val = b[j].val;
				++sz;
                if (base == p-1) {
                    ++base;
                }
				continue;
			}
			c[sz].col = b[j].col;
			c[sz].row = b[j].row;
			c[sz].val = b[j].val;
			ch = true;
            base = j+1;
			break;
		}
		if (ch) {
			c[sz].val += a[i].val;
		} else {
			c[sz].col = a[i].col;
			c[sz].row = a[i].row;
			c[sz].val = a[i].val;
		}
		++sz;
	}
    for (int i = base; i < p; ++i) {
        c[sz].col = b[i].col;
        c[sz].row = b[i].row;
        c[sz].val = b[i].val;
        ++sz;
    }
	return sz;
}

int main() {
	srand(time(0));
	cin >> n;
	
	q = n*n;
	p = q/20;
	
	int A[n][n], B[n][n], C[n][n];
	
	for (long long i = 0; i < q; ++i) {
		A[i/n][i%n] = 0;
		B[i/n][i%n] = 0;
		C[i/n][i%n] = 0;
	}
	
	for (long long i = 0; i < p; ++i) {
		long long ran = rand()%q;
        if (A[ran/n][ran%n] != 0) {
            --i;
            continue;
        }
		A[ran/n][ran%n] = 1+rand()%9;
		ran = rand()%q;
        if (B[ran/n][ran%n] != 0) {
            --i;
            continue;
        }
		B[ran/n][ran%n] = 1+rand()%9;
	}
	cout << "Matrix A:" << endl;
	printArr(A[0], n);
	
	cout << "Matrix B:" << endl;
	printArr(B[0], n);
	
	sumArr(A[0], B[0], C[0], q);
	
	cout << "Matrix C:" << endl;
	printArr(C[0], n);
	
	Sparce a[p], b[p], c[2*p];
	
	sparceArr(A[0], a, n);
	sparceArr(B[0], b, n);
	
	cout << "\nSparce Matrix A:" << endl;
	printSparce(a, p);
	
	cout << "\n\nSparce Matrix B:" << endl;
	printSparce(b, p);
	
	long long csz = sumSparce(a, b, c, p);
	
	cout << "\n\nSparce Matrix c:" << endl;
	printSparce(c, csz);
	
	return 0;
}
