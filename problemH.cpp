#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct compare{
	bool operator()(tuple<int, int, int, int> &t1, tuple<int, int, int, int> & t2){
		if(get<3>(t1) != get<3>(t2)) return get<3>(t1) < get<3>(t2);
	}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<int> arr1(n, 0);
    vector<int> arr2(n, 0);

    for(int i = 0; i < n ; i ++) cin >> arr1[i];
    for(int i = 0; i < n; i ++) cin >> arr2[i];

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, compare> pq;

    for(int i = 0; i < n; i ++){
	pq.emplace(arr1[i], arr2[i], i, max(arr1[i], arr2[i]));
    }

    return 0;

}
