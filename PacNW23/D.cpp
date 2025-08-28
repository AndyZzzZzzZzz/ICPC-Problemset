#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int R, C, d, n;
    cin >> R >> C >> d >> n;
    ll d2 = 1ll*d*d;

    vector<pair<int, int>> centers(n);
    map<int, vector<pair<int, int>>> events;
    for (int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        centers[i] = {r, c};

        // Events at the same row as the center.
        events[r].push_back({max(1, c-d), 1});
        events[r].push_back({min(C, c+d)+1, -1});

        int offset = d;
        for (int dr = 1; dr <= d; dr++) {
            // Decrease offset until within the circle.
            while (1ll*offset*offset + 1ll*dr*dr > d2) offset--;

            // Events on the right side of the circle.
            if (r+dr <= R) {
                events[r+dr].push_back({max(1, c-offset), 1});
                events[r+dr].push_back({min(C, c+offset)+1, -1});
            }
            
            // Events on the left side of the circle.
            if (r-dr >= 1) {
                events[r-dr].push_back({max(1, c-offset), 1});
                events[r-dr].push_back({min(C, c+offset)+1, -1});
            }
        }
    }

    for (auto &[r, by_c] : events) {
        sort(by_c.begin(), by_c.end());
    }
    sort(centers.begin(), centers.end());

    int ans = 1e9;
    for (const auto &[r, by_c] : events) {
        // Check if there is an spot at the start of the row with no overlap.
        if (by_c.begin()->first != 1) return void(cout << "0\n");

        // Use delta encoding (a.k.a. "difference array", etc.).
        int delta = 0;
        for (int i = 0; i < (int)by_c.size(); i++) {
            const auto &[c, t] = by_c[i];
            delta += t;

            // Only consider this position after processing all changes at it (could also use another map instead of pairs).
            if (i == (int)by_c.size()-1 || c != by_c[i+1].first) {
                // Ensure this positon is valid before using it.
                if (c <= C && !binary_search(centers.begin(), centers.end(), pair<int, int>{r, c})) {
                    ans = min(ans, delta);
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solution();
}
