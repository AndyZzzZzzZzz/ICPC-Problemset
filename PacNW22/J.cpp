#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solution() {
    int ds, ys, dm, ym;
    cin >> ds >> ys >> dm >> ym;

    for (int i = 1; i < 5000; i++) {
        int sun_time = -ds+ys*i;
        // int moon_time = -dm+ym*j;
        if ((sun_time+dm)%ym == 0) {
            int j = (sun_time+dm)/ym;
            if (1 <= j) {
                cout << sun_time << '\n';
                return;
            }
        }
    }

    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
