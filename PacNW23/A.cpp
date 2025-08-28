#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    string s;
    cin >> s;
    int n = s.size();

    // Convert to integers for simplicity.
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i]-'A';
    }

    // Should add to masks in decreasing preference of popcount.
    vector<int> order((1<<3)-1);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [](int m1, int m2) -> bool {
        return __builtin_popcount(m1) > __builtin_popcount(m2);
    });

    int ans = 0;
    vector<int> counts((1<<3)-1); // Number of 'active' subsequences in each state ({0,1,2} bits set).
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (auto m : order) {
            if ((m&(1<<a[i])) || !counts[m]) continue; // Check if the mask overlaps and exists.
            found = 1;
            counts[(m^(1<<a[i]))%((1<<3)-1)]++; // Add the current character to the mask. If the mask becomes 7, set it to 0.
            counts[m]--;
            break;
        }

        if (!found) {
            counts[1<<a[i]]++; // Create a new mask with the current character.
            ans++; // This adds to the total cost.
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solution();
}
