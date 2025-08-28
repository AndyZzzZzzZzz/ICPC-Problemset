#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n, m;
    cin >> n >> m;

    // Create a graph representation of the qualifications.
    vector<vector<int>> e_adj(m);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            // There is an edge from service j to engineer i iff s[j] is '1'.
            if (s[j] == '1') {
                e_adj[j].push_back(i);
            }
        }
    }

    // Can bruteforce all possible bitmasks representing which services went down.
    int ans = m;
    for (int mask = 0; mask < (1<<m); mask++) {
        int cnt_right = __builtin_popcount(mask);
        int cnt_left = 0;
        vector<int> inc; // Which engineers are available to fix these services.
        for (int i = 0; i < m; i++) {
            if (mask&(1<<i)) { // Check if this service is down.
                for (auto j : e_adj[i]) { // Add all available engineers.
                    // Check if we already used this engineer.
                    int found = 0;
                    for (auto k : inc) {
                        if (j == k) {
                            found = 1;
                            break;
                        }
                    }

                    if (!found) {
                        cnt_left++;
                        inc.push_back(j);
                    }
                    if (cnt_left >= cnt_right) break; // Can break early by Hall's marriage theorem.
                }
            }
            if (cnt_left >= cnt_right) break; // Can break early by Hall's marriage theorem.
        }

        if (cnt_left < cnt_right) {
            ans = min(ans, cnt_right-1);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solution();
}
