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

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &i : a) cin >> i;

    const int INF = 1e9;
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int r = n-1; r >= 0; r--) {
        for (int l = r-1; l >= 0; l--) {
        }
    }

    int ans = 0;
    int l = 0;
    while (l < n) {
        while (l < n && a[l] == 0) {
            l++;
        }

        int r = l;
        while (r < n-1 && a[r] != 0) {
            r++;
        }

        if (l <= r) {
            ans += dp[l][r];
        }
    }

    return 0;
}
