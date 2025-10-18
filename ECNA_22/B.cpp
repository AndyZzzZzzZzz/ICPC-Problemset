#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bitset<1001> dp[1001];

void solution() {
    int c, n;
    cin >> c >> n;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    dp[0].set(0);

    for (int i = 0; i < n; i++) {
        for (int c1 = c; c1 >= 0; c1--) {
            if (c1+a[i] <= c) {
                dp[c1+a[i]] |= dp[c1];
            }
            dp[c1] |= dp[c1]<<a[i];
        }
    }

    pair<pair<int, int>, pair<int, int>> ans = {{0, 0}, {0, 0}};
    for (int c1 = 0; c1 <= c; c1++) {
        for (int c2 = 0; c2 <= c; c2++) {
            if (dp[c1].test(c2)) {
                ans = max(ans, {{c1+c2, -abs(c1 - c2)}, {c1, c2}});
            }
        }
    }

    // cout << ans.first.first << '\n';
    cout << ans.second.first << ' ' << ans.second.second << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
