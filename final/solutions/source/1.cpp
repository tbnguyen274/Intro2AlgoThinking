/*
BÀI 1: TÌM ĐOẠN CON K PHẦN TỬ CÓ GCD LỚN NHẤT

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- Dãy n số nguyên a_1, a_2, ..., a_n
- Số k (số phần tử liên tiếp cần tìm)

Output:
- GCD lớn nhất của k phần tử liên tiếp

Ví dụ: [2, 6, 4, 3, 18, 12, 24, 8, 7, 5], k=3
Các đoạn con:
- [2,6,4] -> GCD = 2
- [6,4,3] -> GCD = 1
- [4,3,18] -> GCD = 1
- [3,18,12] -> GCD = 3
- [18,12,24] -> GCD = 6 ✓ (MAX)
- [12,24,8] -> GCD = 4
- [24,8,7] -> GCD = 1
- [8,7,5] -> GCD = 1

===== CÁCH 1: BRUTE FORCE - Ý TƯỞNG ĐƠN GIẢN NHẤT =====

Approach:
1. Duyệt qua tất cả các đoạn con k phần tử liên tiếp (có n-k+1 đoạn)
2. Với mỗi đoạn, tính GCD của k phần tử
3. Lưu lại GCD lớn nhất

Độ phức tạp: O(n * k * log(max_a))
- n-k+1 đoạn con
- Mỗi đoạn tính GCD của k số: O(k * log(max_a))

Với n ≤ 1000, k ≤ 1000, a_i ≤ 10^6:
=> O(1000 * 1000 * 20) ≈ 20,000,000 operations
=> Hoàn toàn chấp nhận được!

*/

#include <iostream>
#include <algorithm>
using namespace std;

// Hàm tính GCD của 2 số (Thuật toán Euclid)
// Độ phức tạp: O(log(min(a,b)))
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Hàm tính GCD của k phần tử liên tiếp từ vị trí start
// Độ phức tạp: O(k * log(max_a))
int gcdOfSegment(int arr[], int start, int k) {
    int result = arr[start];
    for (int i = start + 1; i < start + k; i++) {
        result = gcd(result, arr[i]);
        // Tối ưu: nếu GCD đã = 1, không cần tính nữa
        if (result == 1) break;
    }
    return result;
}

// CÁCH 1: BRUTE FORCE
int solution1_bruteforce(int arr[], int n, int k) {
    int maxGCD = 0;
    
    // Duyệt qua tất cả các đoạn con k phần tử
    for (int i = 0; i <= n - k; i++) {
        int currentGCD = gcdOfSegment(arr, i, k);
        maxGCD = max(maxGCD, currentGCD);
    }
    
    return maxGCD;
}

/*
===== CÁCH 2: TÔI ƯU VỚI EARLY STOPPING =====

Quan sát:
- Nếu GCD của một đoạn = 1, không cần tiếp tục tính
- Nếu tìm được GCD = max(a_i), có thể dừng sớm (vì không thể lớn hơn)

Cải tiến:
1. Tìm giá trị lớn nhất trong dãy
2. Nếu đã tìm được GCD = max_value, return ngay
3. Trong tính GCD, nếu = 1 thì break sớm

Độ phức tạp: Vẫn O(n * k * log(max_a)) worst-case
Nhưng average case tốt hơn nhiều!
*/

int solution2_optimized(int arr[], int n, int k) {
    int maxGCD = 0;
    
    // Tìm giá trị lớn nhất trong dãy
    int maxValue = 0;
    for (int i = 0; i < n; i++) {
        maxValue = max(maxValue, arr[i]);
    }
    
    // Duyệt qua tất cả các đoạn con
    for (int i = 0; i <= n - k; i++) {
        int currentGCD = gcdOfSegment(arr, i, k);
        maxGCD = max(maxGCD, currentGCD);
        
        // Early stopping: nếu đã đạt max có thể
        if (maxGCD == maxValue) {
            return maxGCD;
        }
    }
    
    return maxGCD;
}

/*
===== CÁCH 3: TÔI ƯU SLIDING WINDOW (Nếu interviewer hỏi thêm) =====

Có thể nghĩ đến sliding window, nhưng:
- GCD không có tính chất "cộng dồn" như sum
- Khi thêm/bớt 1 phần tử, phải tính lại toàn bộ GCD

Tuy nhiên, có thể cache một số kết quả:
- Lưu GCD từ trái sang phải: leftGCD[i] = GCD(a[0]...a[i])
- Lưu GCD từ phải sang trái: rightGCD[i] = GCD(a[i]...a[n-1])

Nhưng với bài này, do k cố định và n nhỏ (≤ 1000),
cách brute force với early stopping là đủ tốt!

===== KẾT LUẬN TRONG PHỎNG VẤN =====

1. Bắt đầu với brute force để hiểu rõ bài toán
2. Phân tích độ phức tạp -> Nhận thấy đủ tốt với n ≤ 1000
3. Cải tiến với early stopping
4. Giải thích tại sao không cần tối ưu thêm (sliding window không hiệu quả)

Time: O(n * k * log(max_a))
Space: O(1)
*/

int main() {
    int n, k;
    cin >> n >> k;
    
    int arr[1000];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Sử dụng solution tối ưu
    int result = solution2_optimized(arr, n, k);
    
    cout << result << endl;
    
    return 0;
}

/*
===== TEST VỚI VÍ DỤ =====

Input:
10 3
2 6 4 3 18 12 24 8 7 5

Các đoạn con:
i=0: [2,6,4] -> GCD(2,6)=2, GCD(2,4)=2 -> 2
i=1: [6,4,3] -> GCD(6,4)=2, GCD(2,3)=1 -> 1
i=2: [4,3,18] -> GCD(4,3)=1, GCD(1,18)=1 -> 1
i=3: [3,18,12] -> GCD(3,18)=3, GCD(3,12)=3 -> 3
i=4: [18,12,24] -> GCD(18,12)=6, GCD(6,24)=6 -> 6 ✓
i=5: [12,24,8] -> GCD(12,24)=12, GCD(12,8)=4 -> 4
i=6: [24,8,7] -> GCD(24,8)=8, GCD(8,7)=1 -> 1
i=7: [8,7,5] -> GCD(8,7)=1, GCD(1,5)=1 -> 1

Output: 6 ✓
*/
