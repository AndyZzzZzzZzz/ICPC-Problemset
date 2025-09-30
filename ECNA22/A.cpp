#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int m, n, e;
int min_forward[51][51][51][51], min_bumps[51][51][51][51];
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<vector<unsigned char>> adj;
const int INF = 1e9;
const string dir_string = "ENWS"; // NOTE: swapped north and south

void forward(int &r, int &c, int d, int &bumps) {
    if (r == 0) return; // already outside the map (don't move anymore)
    int nr = r+dir[d][0], nc = c+dir[d][1];
    if (adj[r][c]&(1<<d)) {
        return void(bumps++); // move into a wall (invalid move)
    }
    if ((nr <= 0 || nc <= 0 || nr > n || nc > m) && !(nr == 0 && nc == e)) {
        return void(bumps++); // move into a wall (invalid move)
    }
    r = nr, c = nc; // valid move
}

void solution() {
    cin >> m >> n >> e;

    adj.resize(n+1, vector<unsigned char>(m+1, 0b0000));

    char dc1, dc2;
    int c1, r1, c2, r2;
    cin >> c1 >> r1 >> dc1 >> c2 >> r2 >> dc2;

    int d1 = 0, d2 = 0;
    for (int i = 0; i < 4; i++) {
        if (dir_string[i] == dc1) d1 = i;
        if (dir_string[i] == dc2) d2 = i;
    }
    int d2_offset = d2-d1; // since turns don't cost anything, we can iterate
                           // through d1 and compute d2 based on the offset

    int walls;
    cin >> walls;
    while (walls--) {
        int c, r;
        cin >> c >> r;
        adj[r][c] |= 0b0010;
        adj[r+1][c] |= 0b1000;
    }

    cin >> walls;
    while (walls--) {
        int c, r;
        cin >> c >> r;
        adj[r][c] |= 0b0001;
        adj[r][c+1] |= 0b0100;
    }

    for (int i = 0; i <= 50; i++) {
        for (int j = 0; j <= 50; j++) {
            for (int k = 0; k <= 50; k++) {
                for (int l = 0; l <= 50; l++) {
                    min_forward[i][j][k][l] = min_bumps[i][j][k][l] = INF;
                }
            }
        }
    }

    queue<array<int, 4>> q;
    q.push({r1, c1, r2, c2});
    min_forward[r1][c1][r2][c2] = min_bumps[r1][c1][r2][c2] = 0;
    while (q.size()) {
        auto [r1, c1, r2, c2] = q.front();
        q.pop();

        for (int d1 = 0; d1 < 4; d1++) {
            int d2 = (d1+d2_offset+4)%4;
            
            int new_bumps = min_bumps[r1][c1][r2][c2];
            int nr1 = r1, nc1 = c1, nr2 = r2, nc2 = c2;
            forward(nr1, nc1, d1, new_bumps);
            forward(nr2, nc2, d2, new_bumps);

            // robots cannot overlap!!!
            if (nr1 == nr2 && nc1 == nc2 && !(nr1 == 0 && nc1 == e)) {
                continue;
            }

            int new_forward = min_forward[r1][c1][r2][c2]+1;
            if (new_forward < min_forward[nr1][nc1][nr2][nc2]) {
                min_forward[nr1][nc1][nr2][nc2] = new_forward;
                min_bumps[nr1][nc1][nr2][nc2] = new_bumps;
                q.push({nr1, nc1, nr2, nc2});
            } else if (new_forward == min_forward[nr1][nc1][nr2][nc2]) {
                min_bumps[nr1][nc1][nr2][nc2] = min(min_bumps[nr1][nc1][nr2][nc2], new_bumps);
            }
        }
    }

    cout << min_forward[0][e][0][e] << ' ' << min_bumps[0][e][0][e] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
