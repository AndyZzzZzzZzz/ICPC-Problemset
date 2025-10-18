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
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

void solve(){
    /* 
     * Jolie has decided that she needs a specific number of red, green, and blue
     * She found some each, she can but two special types of LEDs, one either red or green
     * and other green or blue
     *
     * How many special LEDs will she need
     */
    int targ_r, targ_g, targ_b; cin >> targ_r >> targ_g >> targ_b;
    int r, g, b; cin >> r >> g >> b;

    int type1, type2; cin >> type1 >> type2;
    
    // amount that we are lacking
    int diff_r = targ_r - r;
    int diff_g = targ_g - g;
    int diff_b = targ_b - b;

    int ans = 0;
    if(diff_r > 0) ans += diff_r;
    if(diff_g > 0) ans += diff_g;
    if(diff_b > 0) ans += diff_b;
    
    // special guard for red and blue because we cannot use both types for those colors
    if(ans > type1 + type2) cout << -1 << '\n';
    else if(diff_r > type1) cout << -1 << '\n';
    else if(diff_b > type2) cout << -1 << '\n';
    else cout << ans << '\n';
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
