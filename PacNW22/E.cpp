#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n;
    cin >> n;

    vector<vector<int>> tubes(n+1);
    for (auto &i : tubes) {
        vector<int> v(3);
        for (auto &j : v) cin >> j;
        for (auto j : v) {
            if (j == 0) break;
            i.push_back(j);
        }
    }

    vector<pair<int, int>> ops;
    auto move_top = [&](int i, int j) -> void {
        assert(tubes[i].size() && (int)tubes[j].size() != 3);
        tubes[j].push_back(tubes[i].back());
        tubes[i].pop_back();
        ops.push_back({i, j});
    };

    auto move_to_empty = [&](int i, int exc=-1) -> void {
        int found_empty = 0;
        for (int j = 0; j < n+1; j++) {
            if (j == exc) continue;
            if ((int)tubes[j].size() < 3) {
                move_top(i, j);
                found_empty = 1;
                break;
            }
        }
        assert(found_empty);
    };

    for (int i = (n+1)-1; i > 0; i--) {
        while (tubes[i].size()) {
            move_to_empty(i);
        }

        vector<vector<vector<int>>> indices(n+1, vector<vector<int>>(3));
        for (int j = 0; j < i; j++) {
            assert((int)tubes[j].size() == 3);
            for (int k = 0; k < 3; k++) {
                indices[tubes[j][k]][k].push_back(j);
            }
        }

        int pivot = -1;
        for (int j = 0; j < i; j++) {
            if ((int)indices[tubes[j][2]][0].size() != 2) {
                pivot = tubes[j][2];
                break;
            }
        }
        assert(pivot != -1);

        for (int k = 2; k >= 0; k--) {
            for (auto j : indices[pivot][k]) {
                while (tubes[j].back() != pivot) {
                    move_to_empty(j, j);
                    assert(tubes[j].size());
                }
                move_top(j, i);
            }
        }
    }

    assert((int)ops.size() <= 9*n);
    cout << ops.size() << '\n';
    for (auto [i, j] : ops) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
