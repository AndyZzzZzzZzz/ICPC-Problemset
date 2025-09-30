#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

void solution() {
    int r, s, h;
    cin >> r >> s >> h;

    double pi = acos(-1);
    double circ = 2*pi*r;
    double T = circ/(s*h);
    int d = round(T);

    pair<double, array<int, 3>> best = {1/.0, {1, 2, 3}};

    for (int n1 = 2; n1 <= 1000; n1++) {
        for (int n2 = n1*2; n2 <= 1000; n2 += n1) {
            for (int n3 = n2*2; n3 <= 1000; n3 += n2) {
                int count_total = n3;
                int count_leap = n3/n1 - n3/n2 + n3/n3;
                double leap_cont = (double)count_leap/count_total;
                double d2;
                if (d < T) {
                    d2 = d + leap_cont;
                } else {
                    d2 = d - leap_cont;
                }

                double diff = abs(d2-T);
                if (diff < best.first) {
                    best = {diff, {n1, n2, n3}};
                }
            }
        }
    }

    for (auto i : best.second) {
        cout << i << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
