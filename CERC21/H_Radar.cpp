// TEST CASES ARE WRONG; EVEN THE PROVIDED SOLUTION CODE GETS WA TEST 42 ON CODEFORCES.
// Of course, the probably was solvable *in contest*. 
// Who knows what happened between then and this codeforces mirror...

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// This Point class is from the KACTL codebook
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point<double> P;

void solution() {
    int r, f, n;
    cin >> r >> f >> n;

    vector<int> radii(r);
    vector<P> dirs(f);
    for (auto &i : radii) cin >> i;
    for (auto &i : dirs) cin >> i.x >> i.y, i = i.unit();

    sort(radii.begin(), radii.end());
    sort(dirs.begin(), dirs.end(), [](const P &p1, const P &p2) -> bool {
        return p1.angle() < p2.angle();
    });

    for (int i = 0; i < n; i++) {
        P p;
        cin >> p.x >> p.y; 

        // Find the two closest angles to the query point
        int left = 0, right = f-1, d_best = 0; 
        while (left <= right) {
            int mid = left+(right-left)/2;
            if (dirs[mid].angle() <= p.angle()) {
                d_best = mid;
                left = mid+1;
            } else {
                right = mid-1;
            }
        }

        double ans = 1/.0; // inf
        for (int k = -1; k <= 1; k++) {
            int j = (d_best+k+f)%f;
            double comp = dirs[j].dot(p); // p = dirs[j]*comp + perp(dirs[j])*something_else
                                          // i.e. comp is the length of the projection (scalar projection function)

            // Find the closest radii to the query point (equivalent to the closest radii to the projection)
            left = 0, right = r-1;
            int r_best = 0;
            while (left <= right) {
                int mid = left+(right-left)/2;
                if (radii[mid] <= comp) {
                    r_best = mid;
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }

            // ans is min dist over all possible distances
            for (int l = max(0, r_best-1); l <= min(r-1, r_best+1); l++) {
                ans = min(ans, (dirs[j]*radii[l]-p).dist());
            }
        }

        cout << fixed << setprecision(6) << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solution();
}
