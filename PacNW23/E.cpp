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

    int n, k; cin >> n >> k;

    vector< vector<int>> matrix(n);
    while(n--){

        int l, r; cin >> l >> r;
        matrix[l].push_back(r);
        matrix[r].push_back(l);
    }


    cout << s << '\n';
    
    return 0;
}
