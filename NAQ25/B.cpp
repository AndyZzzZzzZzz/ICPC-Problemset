#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <climits>
#include <stack>
#include <algorithm>
#include <deque>

using namespace std;

using ll = long long;
using ld = long double;
template<class T> bool chmin(T& a, const T& b){ if(b < a){ a = b; return true; } return false; }
template<class T> bool chmax(T& a, const T& b){ if(a < b){ a = b; return true; } return false; }

#ifdef LOCAL
  #define dbg(x) cerr << "[dbg] " << #x << " = " << (x) << '\n'
#else
  #define dbg(x) ((void)0)
#endif

const ll INF64 = (1LL<<62);
const int INF32 = (1<<30);
const int MOD   = 1'000'000'007; 
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

void solve(){
    // Backup Towers
    int r, c, n; cin >> r >> c >> n;

    vector<vector<int>> grid1(r, vector<int>(c, 0));
    vector<vector<int>> grid2(r, vector<int>(c, 0));
    // double ended queue for multi-source BFS
    deque<tuple<int, int, int>> q;

    for(int i = 0; i < n; ++i)
    {
        int x, y; cin >> x >> y;
        q.push_back({x-1, y-1, i+1});
        grid1[x-1][y-1] = i+1;
    }

    while(!q.empty())
    {
        auto [x, y, id] = q.front(); q.pop_front();

        for(int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i], ny = y + dy[i];

            if(nx >= 0 && ny >= 0 && nx < r && ny < c && (grid1[nx][ny] == 0 || (id != grid1[nx][ny] && grid2[nx][ny] == 0))){
                if(grid1[nx][ny] == 0){
                    grid1[nx][ny] = id;
                }else{
                    grid2[nx][ny] = id;
                }
                q.push_back({nx, ny, id});
            }
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << grid1[i][j] << (j + 1 == c ? '\n' : ' ');
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << grid2[i][j] << (j + 1 == c ? '\n' : ' ');
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
