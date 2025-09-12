#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;


void dfs(int node, bool &check, vector<vector<int>> & adj, unordered_map<int, int>& color, vector<int> &arr){
    
    // Already assigned, skip 
    if(color[node] != -1) return; 
    // traverse neighbor and collect color
    int _arr[3] = {0};
    for(auto n : adj[node]){
        if(color[n] != -1) _arr[color[n]] ++;
    }
    // Assign the first color available
    for(int i = 0; i < 3; ++i){
        if(!_arr[i]){ 
            color[node] = i; arr[i]++;
            // If we reached the current color limits, return false
            if(arr[i] > 6){
                check = false;
                return;
            }
           break;
        }
    }
    
    // Cannot find a valid coloring, return false
    if(color[node] == -1){
        check = false;
        return;
    }
    
    // Assign color for all its neighbor
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
    
    // Map that keep tracks of node -> color
    unordered_map<int, int> color;
    for(int i = 0; i < 26; ++i) color[i] = -1;

    vector<int> words(26, 0);
    for(auto i : s){
        // Check each word contain unique characters
        if(i[0] == i[1] || i[1] == i[2] || i[2] == i[0]){
            cout << 0 << '\n';
            return 0;
        }
        words[i[0] - 'a'] = 1;
        words[i[1] - 'a'] = 1;
        words[i[2] - 'a'] = 1;
    }
    
    // Make sure there are less than 18 unique characters
    int cnt = 0;
    for(int i : words) cnt += i;
    if(cnt > 18){
        cout << 0 << '\n';
        return 0;
    }
    
    // Build adjacency list 
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
        // Only recursive on node with nonempty neighbors
        if(adj[i].size() != 0) dfs(i, check, adj, color, arr);
        // Cann't find a valid color assignment
        if(!check){
           cout << 0 << '\n'; 
           return 0;
        }
    }
   
    // Collect characters that belong to the same color
    unordered_map<int, string> res;
    for(auto c : color){
       if(c.second != -1) res[c.second].push_back((char)(c.first + 'a'));
    }
    // Fill in the rest wih other characters in alphabetical order
    for(auto &r : res){
        for(char c = 'a'; c <= 'z'; c++){
            if(r.second.size() == 6) break;
            if(!words[c-'a']){
                r.second += c;
                words[c-'a'] = 1;
            }
        }
    }
    
    cout << res[0] << ' ' << res[1] << ' ' << res[2] << '\n';

    return 0;
}
