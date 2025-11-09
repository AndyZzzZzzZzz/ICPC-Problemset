#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <climits>
#include <limits>
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
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

void solve(){
    // Curling
    int targ_x = 144, targ_y = 84;
    
    auto calc = [&](int x, int y) -> ll{
        ll dx = x - targ_x, dy = y - targ_y;
        return dx*dx + dy*dy;
    };
    
    int ans_r = 0, ans_y = 0;
    // Take in parameters -> calculate distance to targ -> track winner & points
    for(int i = 0; i < 10; ++i)
    {
        int n; cin >> n;
        vector<ll> dist_r(n);
        for(int j = 0; j < n; ++j){
            int x, y; cin >> x >> y;
            dist_r[j] = calc(x, y);
        }

        int m; cin >> m;
        vector<ll> dist_y(m);
        for(int j = 0; j < m; ++j){
            int x, y; cin >> x >> y;
            dist_y[j] = calc(x, y);
        }

        ll minr = (n==0) ? numeric_limits<ll>::max() : *min_element(dist_r.begin(), dist_r.end());
        ll miny = (m==0) ? numeric_limits<ll>::max() : *min_element(dist_y.begin(), dist_y.end());

        if(minr < miny){
            for(ll d : dist_r) if(d < miny) ans_r++;
            
        }else if(miny < minr){
            for(ll d : dist_y) if(d < minr) ans_y++;
        }
    }

    cout << ans_r << ' ' << ans_y << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
