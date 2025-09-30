#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

void solution() {
    int n, k;
    cin >> n >> k;

    int count = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        string s = to_string(i);
        for (int j = 0; j < (int)s.size(); j++) {
            sum = (sum*10)%k;
        }
        sum = (sum+i)%k;

        count += sum == 0;
    }

    cout << count << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
