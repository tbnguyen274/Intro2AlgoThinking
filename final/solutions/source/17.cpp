/*
BÀI 17: TÌM SỐ NHỎ NHẤT CHỈ CHỨA 0,1 CHIA HẾT CHO N

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- Số nguyên dương n (n ≤ 100)

Output:
- Số nguyên dương m nhỏ nhất thỏa mãn:
  + m chỉ chứa các chữ số {0, 1}
  + m là bội của n (m % n == 0)
  + m có không quá 9 chữ số

Ví dụ: n = 6
- Thử các số: 1, 10, 11, 100, 101, 110, 111, 1000, ...
- 1 % 6 = 1 ✗
- 10 % 6 = 4 ✗
- ...
- 1110 % 6 = 0 ✓
=> Output: 1110

===== CÁCH 1: BRUTE FORCE - SINH TẤT CẢ =====

Approach:
1. Sinh tất cả số chỉ có chữ số 0,1 theo thứ tự tăng dần
2. Kiểm tra từng số xem có chia hết cho n không
3. Trả về số đầu tiên thỏa mãn

Cách sinh:
- Xem như số nhị phân: 1, 10, 11, 100, 101, 110, 111, ...
- Tương đương: 1, 2, 3, 4, 5, 6, 7, ... trong nhị phân
- Chuyển sang số thập phân chỉ có 0,1

Độ phức tạp:
- Time: O(2^k) với k là số chữ số (k ≤ 9)
- Space: O(1)

Với k = 9: 2^9 = 512 số
=> Chấp nhận được!

Vấn đề: 
- Số có thể rất lớn (lên đến 111111111 = 10^9)
- Overflow khi tính toán

===== CÁCH 2: BFS - TÌM KIẾM THEO PHẦN DƯ =====

Key Insight:
- Thay vì lưu số m, lưu phần dư m % n
- Pigeonhole Principle: Có tối đa n phần dư khác nhau (0, 1, ..., n-1)
- Nếu thăm hết n trạng thái, chắc chắn tìm được phần dư = 0

BFS Approach:
1. State: (remainder, number_string)
   - remainder: m % n
   - number_string: chuỗi biểu diễn số m
   
2. Start: (1 % n, "1")
   
3. Transition:
   - Từ state (r, s): sinh 2 state mới
   - Thêm '0': ((r*10) % n, s + "0")
   - Thêm '1': ((r*10 + 1) % n, s + "1")
   
4. Goal: remainder == 0

5. Visited: đánh dấu các remainder đã thăm để tránh lặp

Độ phức tạp:
- Time: O(n) - tối đa n trạng thái
- Space: O(n) - queue và visited

Với n ≤ 100:
- O(100) operations => Rất nhanh!

===== CÁCH 3: BFS TỐI ƯU - CHỈ LƯU REMAINDER =====

Để tiết kiệm space, không lưu chuỗi trong queue:
- Lưu parent và digit để reconstruct path
- parent[r] = remainder trước đó
- digit[r] = chữ số đã thêm (0 hoặc 1)

Reconstruct:
- Bắt đầu từ remainder = 0
- Trace ngược về remainder ban đầu qua parent
- Lưu các digit và reverse

*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ===== SOLUTION 1: BFS VỚI CHUỖI =====
string solution1_bfs_string(int n) {
    if (n == 1) return "1";
    
    queue<pair<int, string>> q; // (remainder, number_string)
    vector<bool> visited(n, false);
    
    q.push({1 % n, "1"});
    visited[1 % n] = true;
    
    while (!q.empty()) {
        int remainder = q.front().first;
        string num_str = q.front().second;
        q.pop();
        
        // Kiểm tra nếu chia hết
        if (remainder == 0) {
            return num_str;
        }
        
        // Kiểm tra độ dài (không quá 9 chữ số)
        if (num_str.length() >= 9) continue;
        
        // Thêm '0'
        int new_remainder_0 = (remainder * 10) % n;
        if (!visited[new_remainder_0]) {
            visited[new_remainder_0] = true;
            q.push({new_remainder_0, num_str + "0"});
        }
        
        // Thêm '1'
        int new_remainder_1 = (remainder * 10 + 1) % n;
        if (!visited[new_remainder_1]) {
            visited[new_remainder_1] = true;
            q.push({new_remainder_1, num_str + "1"});
        }
    }
    
    return "-1"; // Không tìm thấy (không xảy ra)
}

// ===== SOLUTION 2: BFS TỐI ƯU - RECONSTRUCT PATH =====
string solution2_bfs_optimized(int n) {
    if (n == 1) return "1";
    
    queue<int> q;
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> digit(n, -1);
    
    q.push(1 % n);
    visited[1 % n] = true;
    
    int target = -1;
    
    while (!q.empty()) {
        int remainder = q.front();
        q.pop();
        
        if (remainder == 0) {
            target = 0;
            break;
        }
        
        // Thêm '0'
        int new_remainder_0 = (remainder * 10) % n;
        if (!visited[new_remainder_0]) {
            visited[new_remainder_0] = true;
            parent[new_remainder_0] = remainder;
            digit[new_remainder_0] = 0;
            q.push(new_remainder_0);
        }
        
        // Thêm '1'
        int new_remainder_1 = (remainder * 10 + 1) % n;
        if (!visited[new_remainder_1]) {
            visited[new_remainder_1] = true;
            parent[new_remainder_1] = remainder;
            digit[new_remainder_1] = 1;
            q.push(new_remainder_1);
        }
    }
    
    // Reconstruct path
    if (target == -1) return "-1";
    
    string result = "";
    int current = target;
    
    while (parent[current] != -1) {
        result += (char)('0' + digit[current]);
        current = parent[current];
    }
    
    result += "1"; // Số bắt đầu
    reverse(result.begin(), result.end());
    
    return result;
}

// ===== MAIN =====
int main() {
    int n;
    cin >> n;
    
    // Sử dụng BFS với chuỗi (dễ hiểu hơn)
    string result = solution1_bfs_string(n);
    
    cout << result << endl;
    
    return 0;
}

/*
===== TEST VÍ DỤ =====

Input: n = 6

BFS Process:
Queue: [(1, "1")]
Visited: {1}

Step 1: Pop (1, "1")
- remainder = 1 != 0
- Add "10": (1*10) % 6 = 10 % 6 = 4
- Add "11": (1*10+1) % 6 = 11 % 6 = 5
Queue: [(4, "10"), (5, "11")]
Visited: {1, 4, 5}

Step 2: Pop (4, "10")
- remainder = 4 != 0
- Add "100": (4*10) % 6 = 40 % 6 = 4 (visited)
- Add "101": (4*10+1) % 6 = 41 % 6 = 5 (visited)
Skip

Step 3: Pop (5, "11")
- remainder = 5 != 0
- Add "110": (5*10) % 6 = 50 % 6 = 2
- Add "111": (5*10+1) % 6 = 51 % 6 = 3
Queue: [(2, "110"), (3, "111")]
Visited: {1, 2, 3, 4, 5}

Step 4: Pop (2, "110")
- remainder = 2 != 0
- Add "1100": (2*10) % 6 = 20 % 6 = 2 (visited)
- Add "1101": (2*10+1) % 6 = 21 % 6 = 3 (visited)
Skip

Step 5: Pop (3, "111")
- remainder = 3 != 0
- Add "1110": (3*10) % 6 = 30 % 6 = 0 ✓
- Add "1111": (3*10+1) % 6 = 31 % 6 = 1 (visited)
Queue: [(0, "1110")]

Step 6: Pop (0, "1110")
- remainder = 0 => FOUND!

Output: 1110

===== PIGEONHOLE PRINCIPLE =====

Tại sao luôn tìm được đáp án?

Xét dãy: 1, 11, 111, 1111, 11111, ...
- Có n+1 số
- Mỗi số có phần dư trong {0, 1, 2, ..., n-1}
- Theo nguyên lý Dirichlet (Pigeonhole):
  + Có ít nhất 2 số có cùng phần dư
  + Hoặc có 1 số có phần dư = 0

Nếu tồn tại 2 số a và b (a > b) có cùng phần dư:
- a % n = b % n
- (a - b) % n = 0
- a - b có dạng 111...1000...0 (chỉ chứa 0,1)

Vậy luôn tồn tại số chỉ chứa 0,1 chia hết cho n!

===== EDGE CASES =====

1. n = 1: Mọi số đều chia hết => Output: 1

2. n = 2: 
   - 10 % 2 = 0
   => Output: 10

3. n = 5:
   - 1, 10, 11, 100, 101, 110, 111, 1000, ...
   - 10 % 5 = 0
   => Output: 10

4. n = 7:
   - 1 % 7 = 1
   - 10 % 7 = 3
   - 11 % 7 = 4
   - ...
   - 1001 % 7 = 0
   => Output: 1001
*/
