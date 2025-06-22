#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct obj {
	int range;
	int start;
	int end;
	int minn, maxn;

	obj(int r, int s, int e, int mi, int ma) : range(r), start(s), end(e), minn(mi), maxn(ma){}
};

struct compare {
	bool operator()(const obj &p1, const obj &p2){
		return p1.range > p2.range;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
    	cin.tie(0); cout.tie(0);

	priority_queue<obj, vector<obj>, compare> minheap;

	int n; cin >> n;
	vector<int> v(n, 0);

	for(int i = 0; i < n; i ++){
		cin >> v[i];	
	}
	
	if(n < 2){
		cout << "unstable" << endl;
		return 0;
	}

	for(int i = 0; i < n; i ++){
		int x = v[i];
		int y = v[i + 1];
		int minn = min(x, y);
		int maxn = max(x, y);
		minheap.emplace(abs(x - y), i, i + 1, minn, maxn);
	}

	for(int k = 1; k <= n; k ++){

		if(minheap.empty()){
			cout << "unstable" << endl;
			return 0;
		}

		auto curr = minheap.top();
		minheap.pop();

		if(curr.range > k){
			cout << "unstable" << endl;
			return 0;
		}

		if(curr.end + 1 < n){
			int next = curr.end + 1;
			int newmin = min(curr.minn, v[next]);
			int newmax = max(curr.maxn, v[next]);
			minheap.emplace(abs(newmax - newmin), curr.start, next, newmin, newmax);
		}

	}
	cout << "stable" << endl;
	return 0;
}
