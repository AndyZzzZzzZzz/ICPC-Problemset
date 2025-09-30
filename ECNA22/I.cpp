#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--, b--;

    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    int ans = 0;
    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        edges[i] = {x, y, w};
        ans += w;
        dist[x][y] = dist[y][x] = min(dist[x][y], w);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }

    for (auto [x, y, w] : edges) {
        // cout << "edge: " << x << ' ' << y << ' ' << w << '\n';
        // cout << dist[a][x] << ' ' << w << ' ' << dist[y][b] << '\n';

        // a -> x -> (w) y -> b
        if (dist[a][x]+w+dist[y][b] == dist[a][b] || dist[a][y]+w+dist[x][b] == dist[a][b]) {
            // cout << "excluding: " << x << ' ' << y << ' ' << w << '\n';
            ans -= w;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
