#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int s, t, n;
    cin >> s >> t >> n;

    vector<pair<int, int>> by_max(n);
    for (auto &i : by_max) {
        cin >> i.first >> i.second;
    }

    // careful to inc n
    by_max.push_back({t, 0});
    n++;

    sort(by_max.begin(), by_max.end());

    const int INF = 1e9;
    int cur = s;
    int suff_min = INF;
    double total = 0.0;
    for (int i = n-1; i >= 0; i--) {
        if (by_max[i].first >= cur) {
            suff_min = min(suff_min, by_max[i].second);
            continue;
        }
        if (suff_min == INF) {
            return void(cout << "-1\n");
        }
        total += suff_min*log2(cur/(double)by_max[i].first);
        cur = by_max[i].first;
        if (cur == t) break;
        suff_min = min(suff_min, by_max[i].second);
    }

    cout << fixed << setprecision(6) << total << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
