#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &i : a)
    cin >> i;

    // Insert a zero here to represent that we start with the entire range as 0.
    a.insert(a.begin(), 0);
    n++;

    const int INF = 1e9;
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0; // Cost of setting a[i] to a[i] is 0.
    }

    for (int l = n-1; l >= 0; l--) { // Left bound.
        for (int r = l; r < n; r++) { // Right bound.
            for (int m = l; m < r; m++) { // Where we stop the prefix (filled from l to m, inclusive).
                int cur = dp[l][m] + dp[m+1][r] + (a[l]!=a[m+1]); // Cost = cost of prefix + cost of suffix + cost to change value to first value of suffix.
                dp[l][r] = min(dp[l][r], cur);
            }
        }
    }

    int ans = dp[0][n-1];
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solution();
}
