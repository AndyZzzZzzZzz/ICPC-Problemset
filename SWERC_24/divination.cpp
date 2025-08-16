/*
4
0
2 1 4
2 2 4
1 1

-> 1

4
0
1 1
2 2 4
1 1

-> 0
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


vector<int> d;
void dfs(vector<vector<int>>& adj, vector<bool>& seen, int current){
	
	if(seen[current]) return;
	seen[current] = true;
	
	int depth = 0;
	for(int neighb : adj[current]){
		dfs(adj, seen, neighb);
		depth = max(depth, d[neighb]);
	}
	d[current] = depth + 1;

}
int main(){
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    d = vector<int>(n, 0);
    for (int i = 0; i < n; ++i) {
        int ref_count;
        cin >> ref_count;
	
	while(ref_count --){
		int v;
		cin >> v;
		v --;
		adj[i].push_back(v);
	}
    }

    vector<bool> seen(n, false);
    for (int i = 0; i < n; ++i) {
	    if(!seen[i]) {
        	dfs(adj, seen, i);
	    }
        if (d[i] == n) {
            cout << "1" << endl;
            return 0; 
        }
    }

    cout << "0" << endl; 
    return 0;
}
