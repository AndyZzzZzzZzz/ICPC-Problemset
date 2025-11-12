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
#include <unordered_set>

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
  int t; cin >> t;

  unordered_set<ll> squares;
  for(ll i = 0; i*i <= 1000000; ++i) squares.insert(i*i);

  for(int i = 0; i <t; ++i){
    ll n; cin >> n;

    bool odd = false, sq = false;
    if(n & 1) odd = true;
    if(squares.count(n)) sq = true;

    if(sq && odd) cout << "OS" << '\n';
    else if(sq) cout << "S" << '\n';
    else if(odd) cout << "O" << '\n';
    else cout << "EMPTY" << '\n'; 
  }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
