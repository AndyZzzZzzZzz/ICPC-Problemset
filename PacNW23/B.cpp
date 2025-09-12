#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <climits>

using namespace std;

typedef long long ll;

struct Pos { int r, c; };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int r, c;
    if (!(cin >> r >> c)) return 0;

    vector<vector<int>> A(r, vector<int>(c));
    vector<vector<int>> B(r, vector<int>(c));

    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> A[i][j];

    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> B[i][j];

    // current position of each value in A (values are 1..r*c and distinct)
    int N = r * c;
    vector<Pos> pos(N + 1, {-1, -1});
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            pos[A[i][j]] = {i, j};

    // final row of each value (we also keep final col but we don't need it)
    vector<int> finalRow(N + 1, -1);
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            finalRow[B[i][j]] = i;

    // pointer to the leftmost not-yet-filled column in each row of the TARGET
    vector<int> p(r, 0);

    vector<tuple<int,int,int,int>> ops;

    auto doSwap = [&](int r1, int c1, int r2, int c2) {
        int v1 = A[r1][c1], v2 = A[r2][c2];
        swap(A[r1][c1], A[r2][c2]);
        pos[v1] = {r2, c2};
        pos[v2] = {r1, c1};
        ops.emplace_back(r1+1, c1+1, r2+1, c2+1);  // 1-indexed output
    };

    // Process students in globally increasing order of height
    for (int x = 1; x <= N; ++x) {
        int R = finalRow[x];          // target row of x
        int L = p[R];                  // leftmost slot in that row we haven't filled yet

        // If x is already there, lock this column and continue
        if (A[R][L] == x) { p[R]++; continue; }

        // Current location of x
        Pos px = pos[x];
        int S = px.r, Cx = px.c;

        // y is the current occupant of the slot we want to fill
        int y = A[R][L];

        // right neighbor of x in row S (acts as the upper bound we need y to be below)
        auto getRightS = [&]() -> int {
            return (Cx + 1 < c) ? A[S][Cx + 1] : INT_MAX;
        };

        // We will repeatedly lower y by swapping with the largest value < y in row S
        // until y < rightS, then swap x into (R,L).
        while (true) {
            int rightS = getRightS();

            // direct swap is safe iff y < rightS (strict, rows are strictly increasing)
            if (y < rightS) {
                doSwap(R, L, S, Cx);      // x goes to (R,L)
                p[R]++;                   // column L in row R is now fixed
                break;
            }

            // find the largest element < y in row S (must exist because y >= rightS)
            int j = Cx + 1;               // at least the immediate right exists and is < y
            while (j + 1 < c && A[S][j + 1] < y) j++;

            // swap (R,L)'s y with that element; this strictly decreases y and keeps both rows sorted
            doSwap(R, L, S, j);
            y = A[R][L];  // new y after the adjustment swap
            // x is still at (S, Cx), row S remains sorted, loop continues
        }
    }

    cout << (int)ops.size() << '\n';
    for (auto &op : ops) {
        int r1, c1, r2, c2;
        tie(r1, c1, r2, c2) = op;
        cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << '\n';
    }
    return 0;
}
