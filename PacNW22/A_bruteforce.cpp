#include <iostream>
#include <vector>
#include <string>

using namespace std;

// represent letter's connection within words
vector<vector<int>> G(26);
// distinct characers appeard
vector<int> letters;
// color assignment to each die 
// -1 unassigned, 0/1/2 = die
int color[26];
// how many letters currently on each die
int cnt[3];

// check whether a color assignment is legal
bool legal(int u, int c){
    // max capacity for a dice
    if(cnt[c] == 6) return false;
    // neighbor must have different color
    for(int v : G[u]) if(color[v] == c) return false;
    return true;
}

int pick_color(){
    // MRV (Minimum Remaining Values): 
    // choose the letter with the fewest legal dice left
    int best = -1, bestChoices = 4;
    for(int u : letters) if (color[u] == -1) {
        int choices = 0;
        for(int c = 0; c < 3; ++c){
            if(legal(u, c)) ++choices;
        }
        // Can't find valid assignment: backtrack
        if(choices == 0) return -2; 
        if(choices < bestChoices){
            // Choose the letter with minimal options
            best = u;
            bestChoices = choices;
        }
    }
    // -1 indicates we've assigned all colors
    // other wise return the color
    return best;

}

// recursive backtrack function
bool backtrack(){
    
    int u = pick_color();
    if(u == -1) return true;
    if(u == -2) return false;

    for(int c = 0; c < 3; ++c){
        if(legal(u, c)){
            color[u] = c; ++cnt[c];
            
            // early pruning: neighbor must has valid color assignment
            bool ok = true;
            for(int v : G[u]) if(color[v] == -1){
                bool has_color = false;
                for(int d = 0; d < 3; ++d) if(legal(v, d)){
                    has_color = true; break;
                }
                if(!has_color){
                    // can't find a valid color for neighbor
                    ok = false; break;
                }
            }
            if(ok && backtrack()) return true; 
            // backtrack if fail
            --cnt[c]; color[u] = -1;
        }

    }
    return false;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // read inputs
    int n; cin >> n;

    vector<int> used(26, 0);
    for(int i = 0; i < n; ++i){
        string w; cin >> w;

        // must contain distinct letters
        if(w[0] == w[1] || w[1] == w[2] || w[2] == w[0]){
            cout << 0 << '\n'; 
            return 0;
        }

        int a = w[0] - 'a';
        int b = w[1] - 'a';
        int c = w[2] - 'a';
        
        used[a] = used[b] = used[c] = 1;

        G[a].push_back(b);
        G[a].push_back(c);
        G[b].push_back(a);
        G[b].push_back(c);
        G[c].push_back(a);
        G[c].push_back(b);
    }

    // collect unique letters
    for(int i = 0; i < 26; ++i) if(used[i]) letters.push_back(i);
    // can't have more than 18 letters
    if(letters.size() > 18){
        cout << 0 << '\n';
        return 0;
    }

    fill(begin(color), end(color), -1);
    cnt[0] = cnt[1] = cnt[2] = 0;

    if(!backtrack()){
        cout << 0 << '\n';
        return 0;
    }

    // build dice strings from assigned colors
    string dice[3] = {"", "", ""};
    for(int u : letters) dice[color[u]] += char('a' + u);

    // pad with any unused letters
    for(int ch = 0; ch < 26; ch++){
        if(!used[ch]){
            for(int d = 0; d< 3; ++d) if(dice[d].size() < 6){
                dice[d] += char('a' + ch);
                used[ch] ++;
                break;
            }
            if(dice[0].size() + dice[1].size() + dice[2].size() == 18) break;
        }
    }

    cout << dice[0] << ' ' << dice[1] << ' ' << dice[2] << '\n';
    return 0;

}
