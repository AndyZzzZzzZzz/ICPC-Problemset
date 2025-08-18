#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fenwick tree taken from KACTL codebook
#define sz(a) (int)(a).size()
struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) { // a [ pos ] += d i f
        for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) { // sum of values in [0 , pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {// min pos s t sum of [0 , pos ] >= sum
                             // Returns n i f no sum i s >= sum, or =1 i f empty sum i s .
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

void solution() {
	int n;
    cin >> n;
	vector<int> v(n);

	for (int i = 0; i < n-1; i++) cin >> v[i];

	FT f(n);
	for (int i = 0; i < n; i++) f.update(i, v[i]);

	int k; cin >> k;
	
	ll total = accumulate(v.begin(), v.end(), 0ll);
	for(int i = 0; i <= k; ++i){
		if (i > 0) {
			int j, x;
			cin >> j >> x;
			j--;
			int cur_value = f.query(j+1)-f.query(j);
			total -= cur_value, total += x;
			f.update(j, -cur_value);
			f.update(j, x);
		}

		int left = 0, right = n-1, best = -1;
		while(left <= right){
			int mid = (right + left)/2;

			if (f.query(mid) >= total-f.query(mid)) {
				right = mid-1;
				best = mid;
			} else {
                left = mid+1;
            }
		}
		assert(best != -1);
		
		ll ans = LLONG_MAX;
		for (int j = max(0, best-1); j <= best; j++) {
			ll s_left = f.query(j), s_right = total-s_left;
			ans = min(ans, abs(s_left-s_right));
		}
		cout << ans <<'\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	solution();
}

