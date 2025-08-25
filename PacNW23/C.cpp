#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    bool check = true;

    for(int i = 0; i < 3 ; ++i){
        bool local = false;
        for(int j = 0; j< n; ++j){
            int t; cin >> t;
            if(t == 7){
                local = true;
            }
        }
        if(!local) check = false;
    }
    if(check) cout << "777" <<endl;
    else cout << "0" << endl;

    return 0;
}