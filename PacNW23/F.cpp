#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, s, p, q; cin >> n >>m >> s >> p >> q;
    
    set<int> pre_select, want;

    for(int i = 0; i< p; ++i){
        int t; cin >> t;
        pre_select.insert(t);
    }

    for(int i = 0; i<q; ++i){
        int t; cin >> t;
        want.insert(t);
    }
    
    int page = (n + m -1)/m;
    vector<int> cost(page, 0);
    int total = 0;
    for(int i = 0; i < page; ++i){

        int select_all = 1, deselect_all = 1, choose = 0, rm = 0, get = 0;
        int r = min((i+1)*m,n);
        int l = (i*m)+1;
        int count_on_page = r-l+1;
        for(int j = (i*m)+1; j <= min(((i+1)*m), n); ++j){
            if(pre_select.count(j)){
                rm += 1;
                if(!want.count(j)) choose += 1;
            }
            if(want.count(j)){
                get += 1;
                if(!pre_select.count(j)) choose += 1;
            }
        }
        // select all
        select_all += (count_on_page - get);
        // deselect
        deselect_all += get;
        cost[i] = min(choose, min(select_all, deselect_all));
        total += cost[i];
    }
    
    int left =-1, right = -1;
    for(int i = 0; i < page; i ++){
        if(cost[i]){
            if(left == -1) left = i +1;
            right = i + 1;
        }
    }

    if(left == -1) cout << 0 << '\n';
    else cout << min(abs(s-left), abs(s-right)) + (right - left) + total << '\n';
    

    return 0;
}
