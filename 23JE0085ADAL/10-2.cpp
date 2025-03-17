#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    int sum = accumulate(s.begin(), s.end(), 0LL);

    vector<vector<bool>> dp(n + 1, vector<bool>(sum/2 + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum/2; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= s[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - s[i - 1]];
            }
        }
    }

    int x;
    for (x = sum/2; x >= 0; --x) {
        if (dp[n][x]) break;
    }

    cout << "Minimum difference: " << sum - 2*x << "\n";

    return 0;
}
