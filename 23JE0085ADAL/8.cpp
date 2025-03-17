#include <bits/stdc++.h>
using namespace std;

int n, m;

int dfs(int i, int j, const vector<vector<int>>& matrix, vector<vector<int>>& st) {
    if (st[i][j] != -1) return st[i][j];
    vector<int> d(4);
    st[i][j] = 0;
    if (i > 0) {
        if (abs(matrix[i-1][j] - matrix[i][j]) == 1) {
            d[0] = dfs(i-1, j, matrix, st);
        }
    }
    if (i < n-1) {
        if (abs(matrix[i+1][j] - matrix[i][j]) == 1) {
            d[1] = dfs(i+1, j, matrix, st);
        }
    }
    if (j > 0) {
        if (abs(matrix[i][j-1] - matrix[i][j]) == 1) {
            d[2] = dfs(i, j-1, matrix, st);
        }
    }
    if (j < m-1) {
        if (abs(matrix[i][j+1] - matrix[i][j]) == 1) {
            d[3] = dfs(i, j+1, matrix, st);
        }
    }
    sort(d.rbegin(), d.rend());
    st[i][j] = 1+d[0]+d[1];
    return st[i][j];
}

int maxlen(const vector<vector<int>>& matrix) {
    vector<vector<int>> st(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dfs(i, j, matrix, st);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (st[i][j] > ans) ans = st[i][j];
        }
    }

    return ans;
}

// 3 3 1 2 9 5 3 8 4 6 7

int main() {
    cout << "Enter n, m: ";
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    cout << "Enter the matrix: \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Maximum path length = " << maxlen(matrix) << "\n";
    return 0;
}