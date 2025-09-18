#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
#define int ll

using namespace std;

signed main(){
    
    /*
        Strategy:
            1. Simple multipler for pairs
            2. DP for total combinations that make sum of 15
            3. Sliding window for consecutive sequences
    
    */
    int n; cin >> n;
    
    vector<char> v(n);
    int sequence[14] = {0};
    int pairs[14] = {0};
    vector<int> dp(16, 0);
    dp[0] = 1;

    ll points = 0;

    for(int i = 0; i < n; ++i) cin >> v[i]; 

    for (char c : v) {
        for (char d : v) {
            if (c == d) points += 1; // pairs (/2 b/c overcount by 2x because ordered pairs)
        }
    }
    // Subtract overcount
    points -= n;
    
    for(char c : v){
        
        // Parse integer into two values
        // v:  value that contribute to sums that make 15
        // v2: value that contribute to consecutive sequences
        int v = -1, v2 = -1;
        if(c == 'A'){ v =1; v2 = 1;}
        else if(c == 'J' || c == 'T' || c == 'Q' || c == 'K'){ 
            v = 10;
            if(c == 'J') v2 = 11;
            else if(c == 'Q') v2 = 12;
            else if(c == 'T') v2 = 10;
            else v2 = 13;
        }
        else{ 
            v = c - '1'; v2 = c - '1';
            // Account for the differences in offsets
            v++; v2 ++;
        }


        // DP: count the points for sums that make 15 
        sequence[v2]++;
        for(int i = 14; i >= 0; --i){
            int sum = i + v;
            if(sum <= 15) dp[sum] += dp[i];
        }
        
    }
    
    points += (2 * dp[15]);

    // Sliding window for consecutive sequences
    // Sequences stores the frequency for each characters
    int prod = 1, len = 0;
    for (int i = 1; i <= 13; i++) {
        if (sequence[i]) {
            // Any number that contribute to a valid sequence should contribute to points
            prod *= sequence[i];
            len++;
        } else {
            // End of a sequnece, reset length and prod
            if (len >= 3) {
                points += len * prod;
            }
            prod = 1;
            len = 0;
        }
    }
    if (len >= 3) {
        points += len * prod;
    }

    cout << points << '\n'; 
    
    return 0;
}
