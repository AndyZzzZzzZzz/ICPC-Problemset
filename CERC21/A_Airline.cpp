#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n, q;
    cin >> n >> q;

    // input
    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // preprocessing...
    const int MAX_LOG = 25;
    vector<int> depth(n);
    vector<vector<int>> parent(n, vector<int>(MAX_LOG));
    vector<int> subtree_size(n);
    auto precomp = [&](auto &&precomp, int cur, int prev, int d) -> void {
        depth[cur] = d;
        parent[cur][0] = prev;
        subtree_size[cur] = 1;

        for (int i = 1; i < MAX_LOG; i++) {
            parent[cur][i] = parent[parent[cur][i-1]][i-1];
        }

        for (auto i : adj[cur]) {
            if (i == prev) continue;
            precomp(precomp, i, cur, d+1);
            subtree_size[cur] += subtree_size[i];
        }
    };
    precomp(precomp, 0, 0, 0);

    // computes the lca of nodes x and y
    auto lca = [&](int x, int y) -> int {
        if (depth[y] > depth[x]) swap(x, y);
        for (int i = MAX_LOG-1; i >= 0; i--) {
            if (depth[parent[x][i]] >= depth[y]) {
                x = parent[x][i];
            }
        }

        for (int i = MAX_LOG-1; i >= 0; i--) {
            if (parent[x][i] != parent[y][i]) {
                x = parent[x][i], y = parent[y][i];
            }
        }

        if (x == y) return x;
        return parent[x][0];
    };

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        int l = lca(x, y);
        vector<int> x_side_comp_sizes, y_side_comp_sizes;

        // l component is every node not on the path to x or y
        int l_comp_size = n;

        // Find component sizes for x->l path
        int cur = x, prev = -1;
        while (cur != l) {
            int cur_comp_size = subtree_size[cur];
            if (prev != -1) cur_comp_size -= subtree_size[prev];
            x_side_comp_sizes.push_back(cur_comp_size);

            prev = cur;
            cur = parent[cur][0];
        }
        if (prev != -1) l_comp_size -= subtree_size[prev]; // remove nodes on the path to x

        // Find component sizes for y->l path
        cur = y, prev = -1;
        while (cur != l) {
            int cur_comp_size = subtree_size[cur];
            if (prev != -1) cur_comp_size -= subtree_size[prev];
            y_side_comp_sizes.push_back(cur_comp_size);

            prev = cur;
            cur = parent[cur][0];
        }
        if (prev != -1) l_comp_size -= subtree_size[prev]; // remove nodes on the path to y
        reverse(y_side_comp_sizes.begin(), y_side_comp_sizes.end()); // should be l->y instead

        // Compile all vectors into one representing the entire path from x to y
        vector<int> comp_sizes = x_side_comp_sizes;
        comp_sizes.push_back(l_comp_size);
        for (auto j : y_side_comp_sizes) comp_sizes.push_back(j);

        // Compute prefix sums of the component sizes on the path
        int m = comp_sizes.size();
        vector<int> pref(m);
        pref[0] = comp_sizes[0];
        for (int i = 1; i < m; i++) {
            pref[i] = pref[i-1]+comp_sizes[i];
        }

        int affected_range = (m+1)/2-1; // x = ceil(m/2)-1 is the largest integer x such that x < (m+1)/2
                                        // (m/2 -> floor division; (m+1)/2 -> ceil division)
        ll count_shorter = 0;
        for (int i = 0; i < affected_range; i++) {
            int j = m-affected_range+i;
            count_shorter += 1ll*comp_sizes[j] * pref[i];
        }

        cout << count_shorter << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
