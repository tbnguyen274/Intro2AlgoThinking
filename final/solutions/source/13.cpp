/*
BÀI 13: TÌM ĐƯỜNG THẲNG CHIA ĐỀU CÁC ĐIỂM

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- n điểm (n chẵn, n ≤ 10^3)
- Không có 2 điểm trùng nhau
- Không có 3 điểm thẳng hàng
- Tọa độ nguyên |x|, |y| ≤ 10^6

Output:
- 2 số thứ tự của 2 điểm sao cho đường thẳng qua chúng 
  chia n điểm thành 2 phần có số lượng bằng nhau

Ví dụ:
6 điểm: (3,5), (1,3), (3,1), (6,1), (8,3), (6,5)
Output: 2 5 (điểm (1,3) và (8,3))

Đường thẳng y=3:
- Trên đường: 2 điểm (1,3), (8,3)
- Phía trên: 2 điểm (3,5), (6,5)
- Phía dưới: 2 điểm (3,1), (6,1)
=> Mỗi phần có 3 điểm (bao gồm 1 điểm trên đường)

===== CÁCH 1: BRUTE FORCE =====

Approach:
1. Thử tất cả các cặp điểm (i, j)
2. Với mỗi cặp, tạo đường thẳng qua 2 điểm này
3. Đếm số điểm ở mỗi bên của đường thẳng
4. Nếu mỗi bên có đúng n/2 điểm (bao gồm cả 2 điểm trên đường) => Đáp án

Cách xác định điểm nằm bên nào của đường thẳng:
- Dùng Cross Product (tích có hướng)
- Đường thẳng từ A(x1, y1) đến B(x2, y2)
- Điểm P(x, y)
- cross = (x2-x1)*(y-y1) - (y2-y1)*(x-x1)
  + cross > 0: P nằm bên trái đường thẳng AB
  + cross < 0: P nằm bên phải đường thẳng AB
  + cross = 0: P nằm trên đường thẳng AB (không xảy ra do đề bài)

Độ phức tạp:
- Time: O(n^3)
  + Số cặp điểm: C(n,2) = n*(n-1)/2 ≈ O(n^2)
  + Mỗi cặp: kiểm tra n-2 điểm còn lại => O(n)
- Space: O(1)

Với n ≤ 1000:
- O(1000^3) = 10^9 operations
- Hơi chậm nhưng vẫn chấp nhận được!

===== CÁCH 2: TỐI ƯU VỚI EARLY STOPPING =====

Quan sát:
- Nếu tìm được đáp án, return ngay
- Có thể kiểm tra đối xứng: nếu (i,j) không phải đáp án thì (j,i) cũng không

Nhưng về cơ bản vẫn là O(n^3), chỉ cải thiện constant factor.

===== KEY INSIGHT =====

Đường thẳng chia đều n điểm:
- Có đúng n/2 điểm mỗi bên (bao gồm 2 điểm trên đường)
- Hoặc: có (n-2)/2 điểm mỗi bên (không tính 2 điểm trên đường)

Trong code, ta đếm:
- left_count: số điểm bên trái (cross > 0)
- right_count: số điểm bên phải (cross < 0)
- Điều kiện: left_count == right_count == (n-2)/2

*/

#include <iostream>
#include <vector>
using namespace std;

struct Point {
    long long x, y;
    int index; // Số thứ tự từ 1
};

// Tính cross product để xác định vị trí điểm P so với đường thẳng AB
// cross > 0: P bên trái AB
// cross < 0: P bên phải AB
// cross = 0: P trên AB (không xảy ra theo đề)
long long crossProduct(const Point& A, const Point& B, const Point& P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

// Kiểm tra xem đường thẳng qua 2 điểm A và B có chia đều n điểm không
bool checkDivide(const vector<Point>& points, int idxA, int idxB) {
    int n = points.size();
    int left_count = 0;
    int right_count = 0;
    
    const Point& A = points[idxA];
    const Point& B = points[idxB];
    
    // Đếm số điểm ở mỗi bên
    for (int i = 0; i < n; i++) {
        if (i == idxA || i == idxB) continue; // Bỏ qua 2 điểm trên đường
        
        long long cross = crossProduct(A, B, points[i]);
        
        if (cross > 0) {
            left_count++;
        } else if (cross < 0) {
            right_count++;
        }
        // cross == 0: không xảy ra (không có 3 điểm thẳng hàng)
    }
    
    // Kiểm tra chia đều: mỗi bên có (n-2)/2 điểm
    return (left_count == right_count) && (left_count == (n - 2) / 2);
}

// ===== SOLUTION: BRUTE FORCE =====
pair<int, int> solution(vector<Point>& points) {
    int n = points.size();
    
    // Thử tất cả các cặp điểm
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (checkDivide(points, i, j)) {
                // Trả về số thứ tự (từ 1)
                return {points[i].index, points[j].index};
            }
        }
    }
    
    // Không tìm thấy (không xảy ra theo đề)
    return {-1, -1};
}

// ===== MAIN =====
int main() {
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].index = i + 1; // Số thứ tự từ 1
    }
    
    pair<int, int> result = solution(points);
    
    cout << result.first << " " << result.second << endl;
    
    return 0;
}

/*
===== TEST VÍ DỤ =====

Input:
6
3 5
1 3
3 1
6 1
8 3
6 5

Điểm:
1: (3, 5)
2: (1, 3)
3: (3, 1)
4: (6, 1)
5: (8, 3)
6: (6, 5)

Thử cặp (2, 5): điểm (1,3) và (8,3)
Đường thẳng: y = 3 (đường ngang)

Kiểm tra các điểm còn lại:
- Điểm 1: (3, 5) - y > 3 => phía trên (cross > 0)
- Điểm 3: (3, 1) - y < 3 => phía dưới (cross < 0)
- Điểm 4: (6, 1) - y < 3 => phía dưới (cross < 0)
- Điểm 6: (6, 5) - y > 3 => phía trên (cross > 0)

left_count = 2, right_count = 2
(6-2)/2 = 2 => Chia đều!

Output: 2 5

===== CROSS PRODUCT CHI TIẾT =====

Đường thẳng từ A(x1, y1) đến B(x2, y2)
Điểm P(x, y)

Vector AB = (x2-x1, y2-y1)
Vector AP = (x-x1, y-y1)

Cross product (2D):
cross = AB.x * AP.y - AB.y * AP.x
      = (x2-x1) * (y-y1) - (y2-y1) * (x-x1)

Ý nghĩa:
- cross > 0: P ở bên trái AB (quay ngược chiều kim đồng hồ)
- cross < 0: P ở bên phải AB (quay cùng chiều kim đồng hồ)
- cross = 0: P nằm trên đường thẳng AB

Ví dụ cụ thể:
A = (1, 3), B = (8, 3), P = (3, 5)

cross = (8-1) * (5-3) - (3-3) * (3-1)
      = 7 * 2 - 0 * 2
      = 14 > 0
=> P ở bên trái AB (phía trên đường ngang)

===== EDGE CASES =====

1. n = 2: Chỉ có 2 điểm
   => Bất kỳ cặp nào cũng chia đều (mỗi bên 1 điểm)
   => Output: 1 2

2. Điểm tạo thành hình đối xứng:
   => Có nhiều đáp án, chọn cặp đầu tiên tìm được

3. Tọa độ lớn (10^6):
   => Dùng long long để tránh overflow trong cross product
*/
