#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <array>

using namespace std;

// Check whether we have formed ICPC in two rows
bool formsICPC(const string& prev, const string& curr){
    int m = prev.size();

    for(int c = 1; c < m; ++c){
        // check whether we formed ICPC
        if(prev[c-1] == 'I' && prev[c] == 'C' && curr[c-1] == 'P' && curr[c] == 'C') return true;
    }
    return false;
}

void genRows(int c, const string& pattern, string& curr, vector<string>& out){
    int m = pattern.size();
    if(c == m) {out.push_back(curr); return;}
    // try all combinations if ? is on the grid
    if(pattern[c] == '?'){
        for(char ch : {'I', 'C', 'P'}){
            curr[c] = ch;
            genRows(c + 1, pattern, curr, out);
        }
    }else{
        // fixed character case
        curr[c] = pattern[c];
        genRows(c + 1, pattern, curr, out);
    }
}


int main(){
    
    int MOD = 998244353;
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    vector<string> grid(n);
    for(int i = 0; i < n; ++i) cin >> grid[i];

    // Precompute all valid row strings for each input row
    vector<vector<string>> valid(n);
    for(int r = 0; r < n; r ++){
        string curr(m, '?');
        genRows(0, grid[r], curr, valid[r]);
    }

    // DP: map rowString -> {ways_not_found, ways_found}
    unordered_map<string, array<int, 2>> dp, nextdp;

    // Initialization
    for(auto& r: valid[0]) dp[r][0] = (dp[r][0] + 1)%MOD;

    for(int r = 1; r < n; ++r){
        nextdp.clear();
        nextdp.reserve(valid[r].size() * 2);
        
        // Check each previous DP state and current valid filling to see if we
        // can form an ICPC
        for(auto & [prevRow, ways]: dp){
            int w0 = ways[0], w1 = ways[1];
            if(!w0 && !w1) continue;

            for(auto& currRow : valid[r]){
                bool hit = formsICPC(prevRow, currRow);
                // ref is current ways of having one ICPC

                // If we don't have valid filling for previous and hit is true: add w0 to nextDP[1]
                // Else, remain not found
                if(w0){
                    auto& ref = nextdp[currRow][hit ? 1 : 0];
                    ref += w0; if (ref >= MOD) ref -= MOD;
                }
                
                // If previously already found, we stay found regardless of hit and add w1 to ref
                if(w1){
                    auto& ref = nextdp[currRow][1];
                    ref += w1; if (ref >= MOD) ref -= MOD;
                }
            }
        }
        dp.swap(nextdp);
    }
    
    long long ans = 0;
    for(auto & [rows,ways] : dp) ans += ways[1];
    cout << (ans % MOD) << '\n';
    return 0;
}
