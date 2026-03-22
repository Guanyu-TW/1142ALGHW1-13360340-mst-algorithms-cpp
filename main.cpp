#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple> // 補上 tuple 標頭檔
using namespace std;

// ==============================
// 資料結構定義
// ==============================
struct Edge {
    int u, v, w;
};

// 並查集 Disjoint Set Union
class DSU {
private:
    vector<int> parent, rankv;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rankv.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); 
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return false;
        parent[rootA] = rootB;            
        return true;
    }
};

// ==============================
// 工具函式
// ==============================
void printEdge(const Edge& e) {
    cout << e.u << " - " << e.v << " : " << e.w;
}

void printMST(const vector<Edge>& mst) {
    int total = 0;
    cout << "\nMST edges:\n";
    for (const auto& e : mst) {
        printEdge(e);
        cout << "\n";
        total += e.w;
    }
    cout << "Total weight = " << total << "\n";
}

// ==============================
// 1. Kruskal Algorithm Template
// ==============================
void kruskalMST(int n, vector<Edge> edges) {
    cout << "==============================\n";
    cout << "Kruskal Algorithm\n";
    cout << "==============================\n";

    vector<Edge> mst;

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DSU dsu(n);

    cout << "Selection steps:\n";

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            cout << "選取邊: " << e.u << " - " << e.v << " (權重: " << e.w << ")\n";
        } else {
            cout << "捨棄邊: " << e.u << " - " << e.v << " (權重: " << e.w << ") -> 形成迴圈\n";
        }
        if (mst.size() == n - 1) break;
    }

    printMST(mst);
    cout << "\n";
}

// ==============================
// 2. Prim Algorithm Template
//    從 start 開始
// ==============================
void primMST(int n, const vector<vector<pair<int, int>>>& adj, int start = 1) {
    cout << "==============================\n";
    cout << "Prim Algorithm\n";
    cout << "==============================\n";

    vector<bool> inMST(n + 1, false);
    vector<Edge> mst;

    // 最小堆: {權重, from, to}
    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > pq;

    inMST[start] = true;

    for (auto& edge : adj[start]) {
        int to = edge.first;
        int weight = edge.second;
        pq.push({weight, start, to}); 
    }

    cout << "Selection steps:\n";

    while (!pq.empty() && mst.size() < n - 1) {
        // 改用相容性較高的 std::get 寫法，避免 C++17 報錯
        int weight = get<0>(pq.top());
        int from = get<1>(pq.top());
        int to = get<2>(pq.top());
        pq.pop();

        if (inMST[to]) {
            cout << "捨棄邊: " << from << " - " << to << " (權重: " << weight << ") -> 形成迴圈\n";
            continue;
        }

        mst.push_back({from, to, weight});
        inMST[to] = true;
        cout << "選取邊: " << from << " - " << to << " (權重: " << weight << ")\n";

        for (auto& edge : adj[to]) {
            int nextNode = edge.first;
            int nextWeight = edge.second;
            if (!inMST[nextNode]) {
                pq.push({nextWeight, to, nextNode});
            }
        }
    }

    printMST(mst);
    cout << "\n";
}

// ==============================
// 3. Sollin / Boruvka Template
// ==============================
void boruvkaMST(int n, const vector<Edge>& edges) {
    cout << "==============================\n";
    cout << "Sollin / Boruvka Algorithm\n";
    cout << "==============================\n";

    vector<Edge> mst;
    DSU dsu(n);
    
    int numComponents = n;
    int round = 1;

    while (numComponents > 1) {
        cout << "Round " << round << ":\n";

        vector<int> cheapest(n + 1, -1);

        for (int i = 0; i < edges.size(); i++) {
            int set1 = dsu.find(edges[i].u);
            int set2 = dsu.find(edges[i].v);

            if (set1 == set2) continue;

            if (cheapest[set1] == -1 || edges[i].w < edges[cheapest[set1]].w) {
                cheapest[set1] = i;
            }
            if (cheapest[set2] == -1 || edges[i].w < edges[cheapest[set2]].w) {
                cheapest[set2] = i;
            }
        }

        bool merged = false;

        for (int i = 1; i <= n; i++) {
            if (cheapest[i] != -1) {
                int edgeIdx = cheapest[i];
                int u = edges[edgeIdx].u;
                int v = edges[edgeIdx].v;
                int w = edges[edgeIdx].w;

                int set1 = dsu.find(u);
                int set2 = dsu.find(v);

                if (set1 != set2) {
                    dsu.unite(set1, set2);
                    mst.push_back(edges[edgeIdx]);
                    cout << "選取邊: " << u << " - " << v << " (權重: " << w << ")\n";
                    numComponents--; 
                    merged = true;
                }
            }
        }

        if (!merged) break;

        cout << "\n";
        round++;
    }

    printMST(mst);
    cout << "\n";
}

// ==============================
// 主程式
// ==============================
int main() {
    system("chcp 65001 > nul");
    int n = 6;

    // 第 5 題的無向邊資料
    vector<Edge> edges = {
        {1, 2, 16},
        {1, 5, 19},
        {5, 4, 18},
        {2, 4, 6},
        {2, 3, 5},
        {4, 3, 10},
        {1, 6, 22},
        {5, 6, 33},
        {6, 2, 12},
        {6, 4, 14}
    };

    // adjacency list，供 Prim 使用
    vector<vector<pair<int, int>>> adj(n + 1);
    for (const auto& e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    kruskalMST(n, edges);
    primMST(n, adj, 1);
    boruvkaMST(n, edges);

    return 0;
}
