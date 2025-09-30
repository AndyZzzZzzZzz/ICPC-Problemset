#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define X real()
#define Y imag()
typedef complex<ll> P;
ll cross(const P &p1, const P &p2) {
    return (conj(p1)*p2).Y;
}

class segtree {
public:
    segtree(int n) {
        while (sz < n) {
            sz *= 2;
        }
        data.assign(2*sz, 0);
    }

    void update(int i, ll v) {
        update(i, v, 0, 0, sz);
    }

    ll query(int l, int r) {
        return query(l, r, 0, 0, sz);
    }

private:
    int sz = 1;
    vector<ll> data;

    void update(int i, ll v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            data[x] = v;
            return;
        }

        int mid = lx+(rx-lx)/2;
        if (i < mid) update(i, v, 2*x+1, lx, mid);
        else update(i, v, 2*x+2, mid, rx);

        data[x] = data[2*x+1] + data[2*x+2];
    }

    ll query(int l, int r, int x, int lx, int rx) {
        if (l <= lx && rx <= r) return data[x];
        if (r <= lx || rx <= l) return 0;
        
        int mid = lx+(rx-lx)/2;
        ll q1 = query(l, r, 2*x+1, lx, mid);
        ll q2 = query(l, r, 2*x+2, mid, rx);
        return q1+q2;
    }
};

bool CCW(P p1, P p2, P origin) {
    P a = p1-origin;
    P b = p2-origin;
    return cross(a, b) > 0;
}

struct Point {
    P p;
    ll value;
    int index;
};

void solution() {
    int n, x;
    cin >> n >> x;
    P origin_left{0, 0};
    P origin_right{(ll)x, 0};

    vector<Point> points(n);
    int idx = 0;
    for (auto &[p, value, index] : points) {
        ll p_x, p_y;
        cin >> p_x >> p_y >> value;
        p = {p_x, p_y};
        index = idx;
        idx++;
    }
    vector<Point> rad_left = points, rad_right = points;
    sort(rad_left.begin(), rad_left.end(), [origin_left](const Point &p1, const Point &p2) -> bool { return CCW(p1.p, p2.p, origin_left); });
    sort(rad_right.begin(), rad_right.end(), [origin_right](const Point &p1, const Point &p2) -> bool { return CCW(p1.p, p2.p, origin_right); });

    vector<int> to_right_index(n);
    for (int i = 0; i < n; i++) {
        to_right_index[rad_right[i].index] = i;
    }

    segtree st(n);
    for (const auto &[p, value, index] : points) {
        st.update(to_right_index[index], value);
    }

    vector<ll> ans(n);
    for (int i = n-1; i >= 0; i--) {
        const auto &[p, value, index] = rad_left[i];
        st.update(to_right_index[index], 0);

        int left = 0, right = n-1, best = n;
        while (left <= right) {
            int mid = left+(right-left)/2;
            if (CCW(p, rad_right[mid].p, origin_right)) {
                best = mid;
                right = mid-1;
            } else {
                left = mid+1;
            }
        }

        ll cur_ans = st.query(best, n);
        ans[index] = cur_ans;
    }

    for (auto i : ans) {
        cout << i << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
