#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    string s;
    cin >> s;

    int n = s.size();
    
    string order = "ATGC";
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (order[j] == s[i]) {
                a[i] = j;
            }
        }
    }

    vector<vector<int>> counts(4, vector<int>(n+1));
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i <= n; i++) {
            counts[j][i] = counts[j][i-1] + (a[i-1]==j);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        vector<int> cur_counts(4);
        for (int j = 0; j < 4; j++) {
            cur_counts[j] = counts[j][r] - counts[j][l-1];
        }

        vector<pair<int, int>> by_count(4);
        for (int j = 0; j < 4; j++) {
            by_count[j] = {cur_counts[j], -j};
        }

        sort(by_count.rbegin(), by_count.rend());
        for (int j = 0; j < 4; j++) {
            cout << order[-by_count[j].second];
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}

