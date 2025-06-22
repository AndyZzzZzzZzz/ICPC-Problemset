#include <vector>
#include <iostream>

using namespace std;

int main(){

	int n; cin >> n;

	vector<int> v(n, 0);
	int sum = 0;

	for(int i = 0; i < n; i ++){
		cin >> v[i];
		sum += v[i];
	}
	int total = n/2;
	if(n%2 != 0) total = (n - 1)/2;
	int target = sum/2;
	int left = 2, right = total;

	while(left < right){

		int mid = (left + right)/2;
		
		
		if(sum %2 != 0) continue;
	
		total 	

		vector<vector<int>> dp(total + 1, vector<int>(target + 1, 0));
		
		dp[0][0] = 1;
	
		for(int e = 0; e < n; e ++){
			int curr = v[e];
			for(int i = total -1 ; i >= 0; i --){
				for(int j = 0; j <= target - curr; j ++){
					if(dp[i][j]) dp[i + 1][j + curr] = 1;
				}
			}
		}
	
		if(dp[total][target]) cout << total << endl;
	}


	return 0;
}
