#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string f(const string &s) {
    vector<int> counts(10);
    for (auto c : s) {
        counts[c-'0']++;
    }

    string ret;
    for (int i = 0; i <= 9; i++) {
        if (counts[i]) {
            ret += to_string(counts[i]);
            ret += to_string(i);
        }
    }

    return ret;
}

void solution() {
    string start, pattern;
    cin >> start >> pattern;

    set<string> visited;

    for (int i = 1; ; i++) {
        if (start == pattern) {
            cout << i << '\n';
            return;
        }

        start = f(start);
        if (start.size() > 100u) {
            assert(false);
            cout << "I'm bored\n";
            return;
        }

        if (visited.count(start)) {
            cout << "Does not appear\n";
            return;
        }
        visited.insert(start);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
