#include <iostream>
#include <vector>
#include <climits>

using namespace std;
typedef long long ll; 
struct Node {
    int L = 0, R  = 0;  // Child pointers
    ll sum = 0;         // interval sum
    ll pref = 0;        // max prefix∂
    ll suf = 0;         // max suffix
    ll best = 0;        // max subarray
};

class SegTree {
    public:
    
        SegTree(int c) {
            col = c;
            pool.push_back(Node()); // root is special nul/zero node
        }

        int point_add(int root, int pos, ll delta){
            return point_add(root, 1, col, pos, delta);
        }
        
        // Range query on version 'root' over [l, r] (1..M).
        Node query(int root, int l, int r) const {
            return query(root, 1, col, l, r);
        }

    private:
        // store all nodes for all versions
        vector<Node> pool;
        // columns domain
        int col;
        /*
            Node: static makes it a class function instead of an object function
            callable with Node x = SegTree::neutral();
            instead of    SegTree tree; Node x = tree.neutral();

            inline is a compiler hint to embed it directly where used
        */
        // Neutral node: outside of the query range
        static inline Node neutral(){
            Node n; n.sum = n.pref = n.suf = n.best = -(1LL << 60); return n; 
        }
        // Zero node: a segment with value bring 0
        static inline Node zero(){
            Node n; n.sum = n.pref = n.suf = n.best = 0; return n; 
        }

        // Add a new zero node and return the index
        int newZeroNode() {
            pool.push_back(Node());
            return (int)pool.size() - 1;
        }
        // Clone existing node at id an return the index
        int clone(int id) {
            pool.push_back(pool[id]);
            return (int)pool.size() - 1;
        }

        static inline Node merge(const Node& A, const Node& B){
            // Kadane algorithm on segments
            // compute best inside A , best inside B, and best crossing A.suf + B.pref
            if (A.best == -(1LL << 60)) return B;
            if (B.best == -(1LL << 60)) return A;

            Node C;
            C.sum  = A.sum + B.sum;
            C.pref = max(A.pref, A.sum + B.pref);
            C.suf = max(B.suf, B.sum + A.suf);
            C.best = max(A.best, max(B.best, A.suf + B.pref));
            return C;
        }

        int point_add(int id, int L, int R, int pos, long long delta) {
            // id = index of the current node in the pool (0 = implicit zero subtree)
            // [L..R] = segment interval this node covers
            // pos = column index to update
            // delta = value to add to that column
            if (L == R) {
                // Leaf node -> single column case
                // If id != 0 -> this tree has non zero element -> clone it
                // If id == 0 -> this tree is all zero -> build a zero node 
                Node cur = (id ? pool[id] : Node());
                cur.sum += delta;
                cur.pref = cur.suf = cur.best = cur.sum;
                pool.push_back(cur);
                return (int)pool.size() - 1;
            }

            int mid = (L + R) >> 1;
            int nid = id ? clone(id) : newZeroNode();

            int left  = pool[nid].L;
            int right = pool[nid].R;
            
            // Recursive steps
            // If we branch left, right subtree can be reused
            // If we branch right, left subtree can be reused
            if (pos <= mid) {
                // Update goes to left child
                int nl = point_add(left, L, mid, pos, delta);
                // attach new left child
                pool[nid].L = nl;
            } else {
                // Update goes to right child
                int nr = point_add(right, mid + 1, R, pos, delta);
                // attach new right child
                pool[nid].R = nr;
            }
            
            // Get references to left and right children,
            // If child id=0 → treat it as an implicit all-zero node
            const Node &A = (pool[nid].L ? pool[pool[nid].L] : Node());
            const Node &B = (pool[nid].R ? pool[pool[nid].R] : Node());

            // Merge steps
            pool[nid].sum  = A.sum + B.sum;
            pool[nid].pref = max(A.pref, A.sum + B.pref);
            pool[nid].suf = max(B.suf, B.sum + A.suf);
            pool[nid].best = max(A.best, max(B.best, A.suf + B.pref));
            return nid;                          
        }

        Node query(int id, int L, int R, int ql, int qr) const {
            // If out of range, retrun a neutral node that doesn't affect comparison
            if (qr < L || R < ql) return neutral();
            // Within range, return th current node
            if (ql <= L && R <= qr) {
                if (id == 0) return zero();  
                return pool[id];
            }
            int mid = (L + R) >> 1;
            Node left  = query(id ? pool[id].L : 0, L, mid, ql, qr);
            Node right = query(id ? pool[id].R : 0, mid + 1, R, ql, qr);
            return merge(left, right);
        }


};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    int K;
    cin >> K;

    // Collect sparse updates per row: (column, value)
    vector<vector<pair<int, int>>> updates(N + 1);
    for(int i = 0; i < K; ++i){
        int r, c, v; cin >> r >> c >> v;
        updates[r].push_back({c, v});
    }

    // Build persistent versions for heights H=0..N
    SegTree tree(M);
    // roots[H] = version of the tree after rows [1...H]
    vector<int> roots(N+1, 0);
    roots[0] = 0;
    for(int r = 1; r <= N; ++r){
        int root = roots[r-1];
        for(auto [c, v] : updates[r]){
            root = tree.point_add(root, c, v);
        }
        roots[r] = root;
    }

    // Process XOR-encoded queries
    int Q; cin >> Q;
    long long a_m3 = 0, a_m2 = 0, a_m1 = 0;   // Aj-3, Aj-2, Aj-1

    while (Q--) {
        int Hp, Xp, Yp; 
        cin >> Hp >> Xp >> Yp;

        int H = Hp ^ (int)a_m3;
        int X = Xp ^ (int)a_m2;
        int Y = Yp ^ (int)a_m1;

        if (X > Y) swap(X, Y);
        H = max(0, min(H, N));
        X = max(1, min(X, M));
        Y = max(1, min(Y, M));

        auto res = tree.query(roots[H], X, Y);
        long long ans = max(0LL, res.best);
        cout << ans << "\n";

        // Shift window for next query’s decoding
        a_m3 = a_m2;
        a_m2 = a_m1;
        a_m1 = ans;
    }
    return 0;
}