#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string clean(const string &s) {
    string ret;
    for (auto c : s) {
        if (!isspace(c)) {
            ret.push_back(c);
        }
    }
    return ret;
}

void build(const string &s, vector<pair<int, int>> &edges, int &idx, int parent) {
    string v;
    while (idx < (int)s.size() && isdigit(s[idx])) v.push_back(s[idx]), idx++;
    int value = stoi(v);
    edges.push_back({parent, value});
    while (idx < (int)s.size() && s[idx] == '(') {
        idx++;
        build(s, edges, idx, value);
        assert(s[idx] == ')');
        idx++;
    }
}

vector<pair<int, int>> build(const string &s) {
    vector<pair<int, int>> edges;
    int idx = 0;
    build(s, edges, idx, -1);
    sort(edges.begin(), edges.end());

    // cout << "edges:\n";
    // for (auto [x, y] : edges) {
    //     cout << x << ' ' << y << '\n';
    // }
    return edges;
}

void solution() {
    string s, t;
    getline(cin, s), getline(cin, t);

    s = clean(s), t = clean(t);
        
    if (build(s) == build(t)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
