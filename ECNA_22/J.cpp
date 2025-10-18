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


struct Card {
    char r, s;
    int t;
};

void solve(){
    
    vector<Card> dealt;
    dealt.reserve(52);

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 13; ++j){
            string tok; cin >> tok;
            dealt.push_back({tok[0], tok[1], (int)dealt.size()});
        }
    }

    vector<Card> row;
    row.reserve(52);

    auto try_cascade = [&]() -> bool{
        struct Move {
            int type; // 4 cards ot 2 cards
            int idxL; // left index
            int idxR; // right index
            int maxt; // most recent time
        };

        Move best{-1, -1, -1, -1};

        auto better = [&](const Move& a, const Move& b){
            if(b.type == -1) return a;
            if(a.type == -1) return b;
            if(a.type != b.type) return (a.type > b.type) ? a : b;  // moves remove more cards
            if(a.maxt != b.maxt) return (a.maxt  > b.maxt) ? a : b; // newer move 
            return b;
        };

        for(int i = 3; i < row.size(); ++i){
            // same rank cards
            if(row[i].r == row[i-3].r){
                // Find the most recent time in this row
                int maxt = max(max(row[i-3].t, row[i-2].t), max(row[i-1].t, row[i].t));
                Move cand{4, i-3, i, maxt};
                best = better(cand, best);
            }
            // same suit cards
            else if(row[i].s == row[i-3].s){
                int maxt = max(row[i-3].t, row[i].t);
                Move cand{2, i-3, i, maxt};
                best = better(cand, best);
            }
        }

        if(best.type == -1) return false;
        if(best.type == 4){
            row.erase(row.begin() + best.idxL, row.begin() + best.idxL + 4);
        }else{
            row.erase(row.begin() + best.idxR);
            row.erase(row.begin() + best.idxL);
        }
        return true;
    };

    for(auto c : dealt){
        row.push_back(c);
        while (try_cascade()){}
    }

    cout << row.size();
    if(!row.empty()) cout << ' ';
    for(int i = 0; i< row.size(); ++i){
        cout << row[i].r << row[i].s;
        if(i+1 < row.size()) cout << ' ';
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
