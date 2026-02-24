/*
BÀI 21: TÌM CÂY KHUNG NHỎ NHẤT THỨ K

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- N thành phố, M tuyến đường
- K: số thứ tự kế hoạch cần tìm
- Mỗi tuyến đường: (u, v, c) - độ dài c

Output:
- Tổng độ dài các tuyến đường trong kế hoạch thứ K

Bản chất:
- Kế hoạch = Cây khung (Spanning Tree)
- Kế hoạch tối ưu = Cây khung nhỏ nhất (Minimum Spanning Tree - MST)
- Cần tìm: K cây khung nhỏ nhất khác nhau
- Hai kế hoạch khác nhau: có ít nhất 1 cạnh khác

Ví dụ: N=5, M=6, K=2
Các cạnh: (1,2,2), (1,3,4), (2,4,3), (2,5,1), (3,5,5), (4,5,6)
MST 1: {(2,5,1), (1,2,2), (2,4,3), (1,3,4)} = 10
MST 2: {(2,5,1), (1,2,2), (2,4,3), (3,5,5)} = 11

===== CÁCH 1: BRUTE FORCE - LIỆT KÊ TẤT CẢ =====

Approach:
1. Sinh tất cả tập con có N-1 cạnh
2. Kiểm tra xem có tạo thành cây khung không (kết nối tất cả đỉnh)
3. Tính tổng trọng số
4. Sắp xếp và lấy MST thứ K

Độ phức tạp:
- Time: O(C(M, N-1) * N) 
  + C(M, N-1) tập con
  + Mỗi tập kiểm tra O(N) với DSU
- Space: O(M + N)

Với M = 100, N = 100: C(100, 99) ≈ 100
Nhưng với đồ thị dày đặc: C(5000, 99) quá lớn!
=> Không khả thi!

===== CÁCH 2: KRUSKAL + TÌM K-TH MST =====

Key Insight:
- Tìm MST đầu tiên bằng Kruskal
- Để tìm MST thứ 2: Thử thay thế từng cạnh trong MST bằng cạnh khác
- Tổng quát: Sinh các MST khác nhau và giữ K MST nhỏ nhất

Thuật toán:
1. Tìm MST đầu tiên bằng Kruskal
2. Với mỗi cạnh e trong MST:
   - Loại bỏ e
   - Tìm MST mới với các cạnh còn lại
   - Lưu MST mới này
3. Sắp xếp các MST theo tổng trọng số
4. Trả về MST thứ K

Tuy nhiên, cách này chỉ tìm được một số MST, không đầy đủ.

===== CÁCH 3: BEST SOLUTION - ENUMERATE ALL MST =====

Cách đúng nhất:
1. Tìm tất cả các MST bằng cách:
   - Tìm MST đầu tiên
   - Với mỗi cạnh không trong MST, thử thêm vào
   - Khi thêm cạnh mới, tạo cycle, loại bỏ cạnh lớn nhất trong cycle
   - Sinh các MST khác nhau
2. Sử dụng BFS/DFS để duyệt không gian các MST
3. Giữ K MST nhỏ nhất

Với đề bài này (N, M nhỏ), ta có thể dùng cách đơn giản:
- Generate nhiều spanning tree
- Sort và lấy K-th

===== SOLUTION: KRUSKAL + ENUMERATE =====

Approach:
1. Sắp xếp các cạnh theo trọng số
2. Dùng DSU để tìm MST
3. Sinh các cây khung khác nhau bằng cách:
   - Skip một số cạnh và thử cạnh khác
   - Backtracking để sinh các tổ hợp
4. Sort và lấy K-th

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Edge {
    int u, v, cost;
    
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

// ===== DISJOINT SET UNION (DSU) =====
class DSU {
private:
    vector<int> parent, rank;
    
public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false; // Already in same set
        
        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        
        return true;
    }
};

// ===== KRUSKAL'S ALGORITHM =====
long long kruskal(int n, vector<Edge>& edges, vector<int>& skip_indices) {
    DSU dsu(n);
    long long total_cost = 0;
    int edges_used = 0;
    
    set<int> skip_set(skip_indices.begin(), skip_indices.end());
    
    for (int i = 0; i < edges.size(); i++) {
        if (skip_set.count(i)) continue; // Skip this edge
        
        Edge& e = edges[i];
        if (dsu.unite(e.u, e.v)) {
            total_cost += e.cost;
            edges_used++;
            
            if (edges_used == n - 1) break; // MST complete
        }
    }
    
    // Check if we have a valid spanning tree
    if (edges_used == n - 1) {
        return total_cost;
    }
    
    return -1; // Cannot form spanning tree
}

// ===== SOLUTION: FIND K-TH MST =====
long long findKthMST(int n, vector<Edge>& edges, int k) {
    sort(edges.begin(), edges.end());
    
    set<long long> mst_costs; // Use set to store unique MST costs
    int m = edges.size();
    
    // Try all possible combinations of skipping edges
    // Use bitmask to represent which edges to skip
    // But limit the search space
    
    // Simpler approach for small cases:
    // Generate MSTs by trying different edge selections
    for (int mask = 0; mask < (1 << min(m, 15)); mask++) {
        vector<int> skip_indices;
        
        for (int i = 0; i < min(m, 15); i++) {
            if (mask & (1 << i)) {
                skip_indices.push_back(i);
            }
        }
        
        long long cost = kruskal(n, edges, skip_indices);
        if (cost != -1) {
            mst_costs.insert(cost);
            
            // Early stopping if we have enough MSTs
            if (mst_costs.size() > k + 10) break;
        }
    }
    
    // Get K-th smallest
    if (mst_costs.size() >= k) {
        auto it = mst_costs.begin();
        advance(it, k - 1);
        return *it;
    }
    
    return -1;
}

// ===== BETTER SOLUTION FOR THIS PROBLEM =====
// Given small constraints, we can enumerate MSTs more carefully
long long solve(int n, int m, int k, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    
    // Generate all possible spanning trees
    multiset<long long> all_costs;
    
    // Recursive backtracking to generate spanning trees
    function<void(int, DSU&, long long, int)> generate = 
        [&](int idx, DSU& dsu, long long cost, int edges_used) {
        
        if (edges_used == n - 1) {
            all_costs.insert(cost);
            return;
        }
        
        if (idx >= m) return;
        if (all_costs.size() > k * 10) return; // Prune
        
        // Try including this edge
        DSU dsu_copy = dsu;
        if (dsu_copy.unite(edges[idx].u, edges[idx].v)) {
            generate(idx + 1, dsu_copy, cost + edges[idx].cost, edges_used + 1);
        }
        
        // Try not including this edge
        generate(idx + 1, dsu, cost, edges_used);
    };
    
    DSU initial_dsu(n);
    generate(0, initial_dsu, 0, 0);
    
    if (all_costs.size() >= k) {
        auto it = all_costs.begin();
        advance(it, k - 1);
        return *it;
    }
    
    return -1;
}

// ===== MAIN =====
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }
    
    long long result = solve(n, m, k, edges);
    cout << result << endl;
    
    return 0;
}

/*
===== TEST VÍ DỤ =====

Input:
5 6 2
1 2 2
1 3 4
2 4 3
2 5 1
3 5 5
4 5 6

Các cạnh sau khi sort:
(2,5,1), (1,2,2), (2,4,3), (1,3,4), (3,5,5), (4,5,6)

MST 1: {(2,5,1), (1,2,2), (2,4,3), (1,3,4)} = 10
- Chọn (2,5,1): nối 2-5
- Chọn (1,2,2): nối 1-2 (và gián tiếp 1-5)
- Chọn (2,4,3): nối 4 vào
- Chọn (1,3,4): nối 3 vào
- Done: 5 đỉnh, 4 cạnh

MST 2: {(2,5,1), (1,2,2), (2,4,3), (3,5,5)} = 11
- Thay (1,3,4) bằng (3,5,5)

Output: 11

===== DSU (DISJOINT SET UNION) =====

Cấu trúc dữ liệu để quản lý các tập hợp rời rạc:

Operations:
- find(x): Tìm đại diện của tập chứa x
- unite(x, y): Hợp nhất tập chứa x và y

Optimizations:
- Path compression: Trong find(), gán parent[x] = root
- Union by rank: Gắn cây nhỏ vào cây lớn

Time complexity: O(α(n)) ≈ O(1) amortized
α(n) là hàm Ackermann nghịch đảo, rất nhỏ

===== KRUSKAL'S ALGORITHM =====

1. Sắp xếp các cạnh theo trọng số tăng dần
2. Duyệt qua các cạnh:
   - Nếu 2 đỉnh chưa cùng tập: thêm cạnh vào MST
   - Ngược lại: bỏ qua (tạo cycle)
3. Dừng khi có N-1 cạnh

Time: O(M log M + M α(N)) ≈ O(M log M)

*/
