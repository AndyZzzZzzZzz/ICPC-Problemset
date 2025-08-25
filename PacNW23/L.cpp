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

    int n, s; cin >> n >> s;
    while(n--){

        int l, r; cin >> l >> r;

        if(l <= s && s <= r) s++;

    }
    cout << s << '\n';
    
    return 0;
}
