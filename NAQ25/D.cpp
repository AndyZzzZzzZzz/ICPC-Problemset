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
const int dx[4] = {0,-1,0,1}, dy[4] = {1,0,-1,0}; 

void solve(){
    // Carl's Maze - Solving Algorithm
    int n, m; cin >> n >> m;

    int start_r, start_c; cin >> start_r >> start_c;
    int end_r, end_c; cin >> end_r >> end_c;
    
    start_r--; start_c--; end_r--; end_c--;

    vector<string> maze(n);
    // track visited states along with the direction we are facing
    vector<vector<int>> track(n, vector<int>(m, 0));

    for(int i = 0; i < n; ++ i) cin >> maze[i];
    
    if (maze[start_r][start_c] != '0') { cout << 0 << '\n'; return; }

    int count = 0;
    int d = 0;
    // simulation loop
    while(true){
            
        if(start_r == end_r && start_c == end_c) {cout << 1 << 
        '\n'; return;}
        
        // cycle detection
        if(track[start_r][start_c] & (1 << d)) {cout << 0 << '\n'; return; }
        track[start_r][start_c] |= (1 << d);

        int ld = (d+1)%4;
        int lr = start_r + dx[ld], lc = start_c + dy[ld];
        int r = start_r + dx[d], c = start_c + dy[d];

        if(lc >= 0 && lr >= 0 && lr < n && lc < m && maze[lr][lc] == '0')
        {   
            start_r = lr; start_c = lc;
            d = ld;
            count=0;
        }
        else if(r >= 0 && c >= 0 && r < n && c < m && maze[r][c] == '0'){
            start_r = r; start_c = c;
            count=0;
        }else{
            d = ((d+3)%4);
            count ++;
        }

        if(count == 4) {cout << '0' << '\n'; return; }
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
