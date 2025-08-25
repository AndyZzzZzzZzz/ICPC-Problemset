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
    
    int n =  100000;
    vector<int> arr(n, 0);
    arr[0] = 1;
    arr[n-1] = 60000;
    int total = n/2 + 10000;
    cout << total << endl;
    int misses = 33333;

    while(true){
        int x; cin >> x;
        
        if(x == -1){
            bool printed = false;
            for(int i = 0; i <= 100000; ++i){
                if(i%2 == 0) cout << i << endl;
                else if(!arr[i] && !printed){
                    cout << i << endl;
                    printed = true;
                }
            }
            break;
        }
        // guessed
        if(arr[x]){
            
        }else{
            // missed
            if(x-1 >= 0) arr[x-1] += 1;
            if(x+1 < n) arr[x+1] += 1;
            misses -= 1;
        }

    }
    
    return 0;
}
