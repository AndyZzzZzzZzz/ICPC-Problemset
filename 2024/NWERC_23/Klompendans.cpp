#include <queue>
#include <set>
#include <iostream>

using namespace std;

struct Node {
    int x, y, prev;                
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

 
    int mv[2][2];                  
    cin >> mv[0][0] >> mv[0][1];
    cin >> mv[1][0] >> mv[1][1];

    const pair<int,int> sign[4] = {{1,1},{-1,1},{1,-1},{-1,-1}};

    queue<Node> q;
    q.push({0,0,-1});               

    set<tuple<int,int,int>> seen;  
    seen.emplace(0,0,-1);

    while (!q.empty()) {
        auto c = q.front(); q.pop();
        int x = c.x;
        int y = c.y;
        int prev = c.prev;
     
        for (int type = 0; type < 2; ++type) {
            if (prev != -1 && type == prev) continue;   

            int a = mv[type][0];
            int b = mv[type][1];

          
            for (int k = 0; k < 4; ++k) {
                for (int swap = 0; swap < 2; ++swap) {
                    int dx = (swap ? b : a) * sign[k].first;
                    int dy = (swap ? a : b) * sign[k].second;
                    int nx = x + dx, ny = y + dy;

                    if (0 <= nx && nx < n && 0 <= ny && ny < n &&
                        !seen.count({nx,ny,type})) {
                        seen.emplace(nx,ny,type);
                        q.push({nx,ny,type});
                    }
                }
            }
        }
    }

    set<pair<int,int>> coord;
    for (auto const& t : seen) coord.emplace(get<0>(t), get<1>(t));

    cout << coord.size() << '\n';
}
