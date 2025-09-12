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

    // We will build a sequence:
    // 0, (1 or 2), 3, (4 or 5), 6, (7 or 8), ..., 99999, 100000
    // Length k = 66668
    const int MAXV = 100000;
    const int BLOCKS = 33333;         
    const int k = 66668;

    // store the actual sequence
    vector<int> seq(k + 1, -1);
    // maps value -> index in the sequence
    vector<int> pos(MAXV + 1, 0);
    // For each block x, even position is 2x+2; choose[x] = 0 not set, 1 picks 3x+1, 2 picks 3x+2
    // decide which value we want to keep
    vector<int> choose(BLOCKS + 1, 0);

    // Precommit all multiples of 3 (odd positions)
    for (int x = 0; x <= BLOCKS; ++x) {
        int v = 3 * x;                   
        int idx = 2 * x + 1;         
        seq[idx] = v;
        pos[v] = idx;
    }

    seq[k] = 100000;
    pos[100000] = k;

    cout << k << endl;              
    cout.flush();

    while (true) {
        int x; 
        if (!(cin >> x)) return 0;

        if (x == -1) {
            // Fill all not yet committed even positions with 3x+1 by default
            for (int b = 0; b < BLOCKS; ++b) {
                int even_idx = 2 * b + 2;        
                if (seq[even_idx] == -1) {
                    int v = 3 * b + 1;
                    seq[even_idx] = v;
                }
            }
            for (int i = 1; i <= k; ++i) {
                cout << seq[i] << '\n';
            }
            cout.flush();
            break;
        }

        // Already decided value -> return its position
        if (0 <= x && x <= MAXV && pos[x] != 0) {
            cout << pos[x] << endl;
            cout.flush();
            continue;
        }

        // x must be from a pair {3b+1, 3b+2} inside the range (except adversary doesn’t repeat)
        if (1 <= x && x <= MAXV) {
            int b = x / 3;     
            //if b == 33333, only {99999,100000} exists.
            if (b < BLOCKS) {
                int even_idx = 2 * b + 2;
                if (choose[b] == 0) {
                    // First guess from this pair: we keep the other one and report a miss.
                    if (x % 3 == 1) {
                        choose[b] = 2;                 // keep 3b+2
                        int keep = 3 * b + 2;
                        seq[even_idx] = keep;
                        pos[keep] = even_idx;
                    } else {
                        choose[b] = 1;                 // keep 3b+1
                        int keep = 3 * b + 1;
                        seq[even_idx] = keep;
                        pos[keep] = even_idx;
                    }
                    cout << -1 << endl;                // miss
                    cout.flush();
                    continue;
                } else {
                    // Already committed; answer accordingly.
                    int kept = (choose[b] == 1) ? (3 * b + 1) : (3 * b + 2);
                    if (x == kept) {
                        cout << even_idx << endl;
                    } else {
                        cout << -1 << endl;   
                    }
                    cout.flush();
                    continue;
                }
            }
        }

        cout << -1 << endl;
        cout.flush();
    }

    return 0;
}
