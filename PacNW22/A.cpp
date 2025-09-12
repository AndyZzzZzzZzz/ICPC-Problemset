#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;


void dfs(int node, bool &check, vector<vector<int>> & adj, unordered_map<int, int>& color, vector<int> &arr){
    
    if(color[node] != -1) return; 
    // traverse neighbor and collect color
    int _arr[3] = {0};
    for(auto n : adj[node]){
        if(color[n] != -1) _arr[color[n]] ++;
    }
    for(int i = 0; i < 3; ++i){
        if(!_arr[i]){ 
            color[node] = i; arr[i]++;
            if(arr[i] > 6){
                check = false;
                return;
            }
           break;
        }
    }
    
    
    if(color[node] == -1){
        check = false;
        return;
    }
    
    for(auto n : adj[node]) dfs(n, check, adj, color, arr);
    return;
}

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    
    vector<string> s(n);
    for(int i = 0; i < n; ++i) cin >> s[i];
    
    vector<vector<int>> adj(26);
    
    unordered_map<int, int> color;
    for(int i = 0; i < 26; ++i) color[i] = -1;

    unordered_map<char, int> unique;
    for(auto i : s){
        set<char> check(i.begin(), i.end());
        if(check.size() != 3){
            cout << 0 << '\n';
            return 0;
        }
        for(auto c : i){
            if(!unique.count(c)) unique[c] = unique.size();
        }
    }

    if(unique.size() > 18) {cout << 0 << '\n'; return 0;}
    

        for(auto i : s){
            int a = (i[0]-'a'), b = (i[1]- 'a'), c = (i[2] - 'a');
            adj[a].push_back(b);
            adj[a].push_back(c);
            adj[b].push_back(a);
            adj[b].push_back(c);
            adj[c].push_back(a);
            adj[c].push_back(b);
        }

    
    bool check = true;
    vector<int> arr = {0, 0, 0};
    for(int i = 0; i < 26; ++i){
        if(adj[i].size() != 0)dfs(i, check, adj, color, arr);
        if(!check){
           cout << 0 << '\n'; 
           return 0;
        }
    }
    
    unordered_map<int, string> res;
    for(auto c : color){
       if(c.second != -1) res[c.second].push_back((char)(c.first + 'a'));
    }
    for(auto &r : res){
        for(char c = 'a'; c <= 'z'; c++){
            if(r.second.size() == 6) break;
            if(!unique.count(c)){
                r.second += c;
                unique[c] = 1;
            }
        }
    }
    
    cout << res[0] << ' ' << res[1] << ' ' << res[2] << '\n';

    return 0;
}
