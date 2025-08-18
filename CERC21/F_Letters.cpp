#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void rot_cw(vector<string> &mat) {
	int n = mat.size(), m = mat[0].size();
	vector<string> res(m, string(n, '.'));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res[j][n-1-i] = mat[i][j];
		}
	}
	mat = res;
}

void pull_left(vector<string> &mat) {
	int n = mat.size(), m = mat[0].size();
	vector<string> res(n, string(m, '.'));
	for (int i = 0; i < n; i++) {
		int rj = 0;
		for (int mj = 0; mj < m; mj++) {
			if (mat[i][mj] != '.') {
				res[i][rj++] = mat[i][mj];
			}
		}
	}
	mat = res;
}

void solution() {
	int n, m, k;
	string s;
	cin >> n >> m >> k;

	if (k) cin >> s;

	vector<string> mat(n);
	for (auto &i : mat) cin >> i;

	for (auto c : s) {
		if (c == 'L') {
			pull_left(mat);
		} else if (c == 'R') {
			rot_cw(mat), rot_cw(mat);
			pull_left(mat);
			rot_cw(mat), rot_cw(mat);
		} else if (c == 'D') {
			rot_cw(mat);
			pull_left(mat);
			rot_cw(mat), rot_cw(mat), rot_cw(mat);
		} else if (c == 'U') {
			rot_cw(mat), rot_cw(mat), rot_cw(mat);
			pull_left(mat);
			rot_cw(mat);
		}
	}

	for (auto i : mat) {
		for (auto j : i) {
			cout << j;
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	solution();
}

