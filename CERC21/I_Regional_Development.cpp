#include <vector>
#include <iostream>
using namespace std;

/*
   Implementation of Ford–Fulkerson with DFS for augmenting paths.
   We'll use this to solve the merchant balancing problem.
*/
struct FordFulkerson {
    // Each directed edge in the residual graph
    struct Edge {
        int to;     // destination node
        int cap;    // residual capacity on this edge
        int rev;    // index of the reverse edge in adjacency list of 'to'
    };

    int numNodes;
    vector<vector<Edge>> graph;  // adjacency list representation
    vector<int> visited;         // marks nodes visited in a DFS iteration

    FordFulkerson(int n) : numNodes(n), graph(n), visited(n) {}

    // Add a directed edge from 'from' to 'to' with initial capacity 'cap'
    // Also add the reverse edge with capacity 0 for residual graph
    int add_edge(int from, int to, int cap) {
        Edge forward = {to, cap, (int)graph[to].size()};
        Edge backward = {from, 0, (int)graph[from].size()};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
        return (int)graph[from].size() - 1; // return index of forward edge
    }

    // Depth-First Search to try to send 'flowToPush' units from current node to sink
    int dfs(int current, int sink, int flowToPush) {
        if (current == sink) return flowToPush; // reached sink, push flow
        visited[current] = 1; // mark node visited
        for (auto &edge : graph[current]) {
            if (!visited[edge.to] && edge.cap > 0) {
                int pushed = dfs(edge.to, sink, min(flowToPush, edge.cap));
                if (pushed > 0) {
                    // Reduce forward capacity by pushed amount
                    edge.cap -= pushed;
                    // Increase backward edge capacity (undo option)
                    graph[edge.to][edge.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0; // no flow could be pushed
    }

    // Run Ford–Fulkerson until no more augmenting path exists
    long long maxflow(int source, int sink) {
        long long totalFlow = 0;
        while (true) {
            fill(visited.begin(), visited.end(), 0);
            int pushed = dfs(source, sink, INT_MAX);
            if (pushed == 0) break; // no augmenting path found
            totalFlow += pushed;
        }
        return totalFlow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numVillages, numRoads, M;
    cin >> numVillages >> numRoads >> M;

    // Store input roads
    struct Road { int from, to, merchants; };
    vector<Road> roads(numRoads);
    for (int i = 0; i < numRoads; ++i) {
        cin >> roads[i].from >> roads[i].to >> roads[i].merchants;
    }

    // -------- Step 1: compute imbalance d(v) = (inflow - outflow)/M --------
    vector<long long> inflow(numVillages, 0), outflow(numVillages, 0);

    // Count inflow/outflow from the given merchant assignment
    for (auto &rd : roads) {
        int u = rd.from - 1; // zero-based index
        int v = rd.to - 1;
        inflow[v]  += rd.merchants;
        outflow[u] += rd.merchants;
    }

    // d[v] tells how many units of M need to leave (-) or enter (+) this village
    vector<long long> imbalance(numVillages, 0);
    long long totalExcess = 0;
    for (int v = 0; v < numVillages; ++v) {
        long long diff = inflow[v] - outflow[v];
        if (diff % M != 0) {
            cout << "IMPOSSIBLE\n"; // input guarantee, but safety check
            return 0;
        }
        imbalance[v] = diff / M;
        if (imbalance[v] > 0) totalExcess += imbalance[v]; // track total units
    }

    // -------- Step 2: Build auxiliary flow network --------
    // Nodes: 0..N-1 for villages, plus super-source S and super-sink T
    int S = numVillages;
    int T = numVillages + 1;
    FordFulkerson ff(numVillages + 2);

    // Keep references to forward arcs for each original road
    vector<pair<int,int>> roadArcRef(numRoads);

    // Add original roads as arcs with capacity 1
    // Means: each road can be "flipped" (subtract M) at most once
    for (int i = 0; i < numRoads; ++i) {
        int u = roads[i].from - 1;
        int v = roads[i].to - 1;
        int arcIndex = ff.add_edge(u, v, 1);
        roadArcRef[i] = {u, arcIndex};
    }

    // Connect S to deficit nodes, and excess nodes to T
    for (int v = 0; v < numVillages; ++v) {
        if (imbalance[v] < 0) {
            ff.add_edge(S, v, (int)(-imbalance[v])); // supply from deficit
        } else if (imbalance[v] > 0) {
            ff.add_edge(v, T, (int)imbalance[v]); // demand at excess
        }
    }

    // -------- Step 3: Run Ford–Fulkerson --------
    long long flow = ff.maxflow(S, T);
    if (flow != totalExcess) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // -------- Step 4: Build final merchant assignment --------
    for (int i = 0; i < numRoads; ++i) {
        int u = roadArcRef[i].first;
        int idx = roadArcRef[i].second;
        // If forward arc cap==0, that edge carried 1 unit in max-flow -> subtract M
        int used = (ff.graph[u][idx].cap == 0) ? 1 : 0;
        int finalMerchants = roads[i].merchants - used * M;
        cout << finalMerchants << "\n"; // negative = opposite direction
    }

    return 0;
}