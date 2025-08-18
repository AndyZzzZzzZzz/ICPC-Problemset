#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct repetition {
    int length, pos;
    bool operator<(const repetition &other) const {
        return length < other.length || (length == other.length && pos > other.pos);
    }
    bool operator==(const repetition &other) const {
        return length == other.length && pos == other.pos;
    }
};

vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r-i+1, z[i-l]);
        }
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i, r = i+z[i]-1;
        }
    }
    return z;
}

int get_z(const vector<int> &z, int i) {
    if (0 <= i && i < (int)z.size()) return z[i];
    return 0;
}

repetition main_lorentz_merge(const string &s, int mid) {
    int n = s.size();
    int nu = mid;
    int nv = n-nu;

    string u = s.substr(0, nu);
    string v = s.substr(nu);
    string ru(u.rbegin(), u.rend());
    string rv(v.rbegin(), v.rend());

    vector<int> z1 = z_function(ru);
    vector<int> z2 = z_function(v+'#'+u);
    vector<int> z3 = z_function(ru+'#'+rv);
    vector<int> z4 = z_function(v);

    repetition best = {0, 0};
    for (int center = 0; center < n; center++) {
        int l, k1, k2;
        if (center < nu) {
            l = nu-center;
            k1 = get_z(z1, nu-center);
            k2 = get_z(z2, nv+1+center);
        } else {
            l = center-nu+1;
            k1 = get_z(z3, nu+1+nv-1-(center-nu));
            k2 = get_z(z4, (center-nu)+1);
        }
        if (k1+k2 >= l) {
            int len = l, pos;
            int left = center < nu;

            // Some magic here. Don't ask about it, please.
            // Try to maximize l1, but sometimes it seems like it cannot be max_l1.
            int max_l1 = min(l, k1);
            for (int l1 = max({1, l-k2, max_l1-1}); l1 <= max_l1; l1++) {
                if (left && l1 == l) break;
                pos = left ? center-l1 : center-l-l1+1;
                best = max(best, {len, pos});
            }
        }
    }

    return best;
}

repetition main_lorentz_merge(const string &s, int l, int mid, int r) {
    repetition res = main_lorentz_merge(s.substr(l, r-l), mid-l);
    res.pos += l;
    return res;
}

class segtree {
public:
    segtree(const string &s) {
        n = s.size();
        while (sz < n) sz *= 2;
        nodes.resize(2*sz);

        this->s = s;

        build(0, 0, sz);
    }

    repetition query(int l, int r) {
        return query(l, r, 0, 0, sz).result;
    }

private:
    struct node {
        int left, right;
        repetition result;
        bool operator==(const node &other) const {
            return tie(left, right, result) == tie(other.left, other.right, other.result);
        }
    };

    int sz = 1, n;
    string s;
    vector<node> nodes;

    const node INVALID_NODE = {-1, -1, {-1, -1}};

    node merge(const node &n1, const node &n2) {
        if (n2 == INVALID_NODE) return n1;
        if (n1 == INVALID_NODE) return n2;
        assert(n1.right == n2.left);
        return {n1.left, n2.right, max({n1.result, n2.result, main_lorentz_merge(s, n1.left, n1.right, n2.right)})};
    }

    void build(int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < n) {
                nodes[x] = node{lx, rx, repetition{0, lx}};
            } else {
                nodes[x] = INVALID_NODE;
            }
            return;
        }

        int mid = lx+(rx-lx)/2;
        build(2*x+1, lx, mid);
        build(2*x+2, mid, rx);
        nodes[x] = merge(nodes[2*x+1], nodes[2*x+2]);
    }

    node query(int l, int r, int x, int lx, int rx) {
        if (l <= lx && rx <= r) return nodes[x];
        if (rx <= l || r <= lx) return INVALID_NODE;

        int mid = lx+(rx-lx)/2;
        node q1 = query(l, r, 2*x+1, lx, mid);
        node q2 = query(l, r, 2*x+2, mid, rx);
        return merge(q1, q2);
    }
};

void solution() {
    int n, q;
    string s;
    cin >> n >> q >> s;

    segtree st(s);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;

        repetition res = st.query(l, r);
        cout << res.length << ' ' << res.pos+1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
