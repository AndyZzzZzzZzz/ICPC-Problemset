// 5
// 7 3 2 100 1
// -> 6
// 8
// 45 13 18 10 8 56 17 19
// -> 13 

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

int main(){
	
	long long res = 0;
	long long n;
	cin >> n;
	vector<long long> temp;
	long long g_max = 0;
	unordered_set<long long> st;

	for(auto i = 0; i < n; i ++){
				
		long long curr; cin >> curr;
		if(curr > g_max){
			g_max = curr;
		}
		temp.push_back(curr);
	}

	for(auto  i = 0; i < n; i ++) if(temp[i] == g_max) st.insert(i);
	
	stack<long long> stk;
	vector<long long> right_dist(n, INT_MAX);
	for(auto i = 0; i < n; i ++){
		while(!stk.empty()  && temp[i] > temp[stk.top()]) {
			long long id = stk.top(); stk.pop();
			right_dist[id] = i - id;
		}
		stk.push(i);
	}
	
	while(!stk.empty()) stk.pop();

	vector<long long> left_dist(n, INT_MAX);
	for(auto i = n - 1; i >= 0; i --){
		while(!stk.empty()  && temp[i] > temp[stk.top()]) {
			long long id = stk.top(); stk.pop();
			left_dist[id] = id - i;
		}
		stk.push(i);
	}
	


	for(long long i = 0; i < n; i ++){
		if(st.count(i)) continue;
		res += min(left_dist[i], right_dist[i]);
	}

	cout << res << endl;

	return 0;
}

