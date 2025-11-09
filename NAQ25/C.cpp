#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
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
    // Call for problems, round 2
    int n, k; cin >> n >> k;
    unordered_set<int> s;

    while(n--){
        int d; cin >> d;
        s.insert(d);
    }

    if(s.size() > k) cout << k << '\n';
    else cout << s.size() << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
