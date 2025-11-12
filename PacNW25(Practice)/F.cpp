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
   int p, t; cin >> p >> t;

   vector<string> teams;
   teams.reserve(t);

   for(int i = 0; i < t; ++i){
      string tmp; cin >> tmp; 
      
      bool check = true;
      int arr[26] = {0};
      for(char c : tmp){
        int idx = c - 'A';
        if(idx >= p){ check = false; break; }  
        if(arr[idx]){ check = false; break; } 
        arr[idx] = 1;
      }
      if(check) teams.push_back(tmp);
   }

   int used[26] = {0};
   int ans = 0;

   // backtrack
   auto dfs = [&](int pos, vector<string>& curr, auto && dfs) -> void
   {
      if ((int)curr.size() + (int)teams.size() - pos <= ans) return;
      if(pos == (int)teams.size()){
        ans = max(ans, (int)curr.size()); 
        return;
      }

      // skip
      dfs(pos+1, curr, dfs);

      ans = max(ans, (int)curr.size());
      bool check = true;
      for(char c : teams[pos]){
        int idx = c - 'A';
        if(used[idx]){ check = false; break; }
      }

      // use
      if(check) {
        for(char c : teams[pos]){
          used[c-'A']++;
        }
        curr.push_back(teams[pos]);
        dfs(pos+1, curr, dfs);
        // backtrack
        for(char c : curr.back()){
          used[c-'A']--;
        }
        curr.pop_back();
      }
   };

   vector<string> curr;
   dfs(0, curr, dfs);
   cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
