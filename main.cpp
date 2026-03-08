#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
        // TODO:
        // 1. 若 parent[x] != x，遞迴尋找根
        // 2. 可加入 path compression
        // 3. 回傳集合代表元
        return x; // 請修改
    }

    bool unite(int a, int b) {
        // TODO:
        // 1. 找 a, b 的根
        // 2. 若相同代表已在同一集合，回傳 false
        // 3. 否則合併兩集合，回傳 true
        return false; // 請修改
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

    // TODO:
    // Step 1. 將 edges 依照權重由小到大排序

    // TODO:
    // Step 2. 建立 DSU 物件

    cout << "Selection steps:\n";

    // TODO:
    // Step 3. 逐一檢查排序後的每條邊
    //   - 若加入後不形成 cycle，則選入 mst
    //   - 否則略過
    //   - 當 mst.size() == n - 1 時停止

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

    // TODO:
    // Step 1. 將起點 start 設為已加入 MST

    // TODO:
    // Step 2. 把 start 相鄰的邊放入 priority queue

    cout << "Selection steps:\n";

    // TODO:
    // Step 3. 當 pq 不為空且 mst 邊數 < n-1
    //   - 取出最小邊
    //   - 若 to 已在 MST 中，跳過
    //   - 否則加入此邊到 mst，並把新頂點標記進 MST
    //   - 再將新頂點可到達的候選邊放入 pq

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

    // TODO:
    // Step 1. 建立 DSU
    // Step 2. 初始 component 數量為 n

    int numComponents = n;
    int round = 1;

    while (numComponents > 1) {
        cout << "Round " << round << ":\n";

        // cheapest[i] = 第 i 個 component 目前找到的最便宜邊的 index
        vector<int> cheapest(n + 1, -1);

        // TODO:
        // Step 3. 掃描所有邊，對每個 component 找 cheapest edge
        // 提示：
        //   set1 = find(edges[i].u)
        //   set2 = find(edges[i].v)
        //   若 set1 == set2，代表同一 component，跳過
        //   否則更新 cheapest[set1] 與 cheapest[set2]

        bool merged = false;

        // TODO:
        // Step 4. 將每個 component 找到的 cheapest edge 嘗試加入 MST
        //   - 若兩端點屬於不同 component，則合併
        //   - 加入 mst
        //   - numComponents--
        //   - merged = true

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
    int n = 6;

    // 圖中的無向邊
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
