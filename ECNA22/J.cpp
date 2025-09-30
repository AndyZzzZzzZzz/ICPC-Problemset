#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n = 52;
    vector<pair<char, char>> cards;
    while (n--) {
        pair<char, char> cur;
        cin >> cur.first >> cur.second;
        cards.push_back(cur);

        while (1) {
            int changed = 0;

            vector<pair<pair<int, int>, pair<int, int>>> moves;
            for (int i = 0; i < (int)cards.size()-3; i++) {
                if (cards[i].first == cards[i+3].first) {
                    moves.push_back({{1, i}, {i, i+3}});
                }
                if (cards[i].second == cards[i+3].second) {
                    moves.push_back({{0, i}, {i, i+3}});
                }
            }

            sort(moves.rbegin(), moves.rend());

            if (moves.size()) {
                auto [p1, p2] = *moves.begin();
                auto [i, j] = p2;
                if (cards[i].first == cards[j].first) {
                    for (int k = 0; k < 4; k++) {
                        cards.erase(cards.begin()+i);
                    }
                } else {
                    cards.erase(cards.begin()+i);
                    cards.erase(cards.begin()+i+3-1);
                }
                changed = 1;
            }

            if (!changed) break;
        }
    }

    cout << cards.size() << ' ';
    for (auto [r, s] : cards) {
        cout << r << s << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
