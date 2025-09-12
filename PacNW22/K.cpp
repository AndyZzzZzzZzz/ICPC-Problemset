#include <iostream>
#include <vector>

using namespace std;

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    vector<vector<char>> matrix(n, vector<int>(m));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> matrix[i][j];
        }
    }
    
    int MOD = 998244353;
    int ans = 0;

    for(int i = 0; i < n/2; ++i){
        bool possible = true;
        int marks = 0;
        for(int j = 0; j < m/2; ++j){
            
        }
            
    }

    return 0;
}
