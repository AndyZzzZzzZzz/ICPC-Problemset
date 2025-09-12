#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> a(n);
    ll S = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        S += a[i];
        if (a[i] > mx) mx = a[i];
    }

    // minimal number of bags b* so that all produced candies can fit
    ll b = max(mx, (S + k - 1) / k);   // ceil(S / k)

    // minimum extra candies to order
    ll extra = b * 1LL * k - S;

    cout << extra << '\n';
    return 0;
}
