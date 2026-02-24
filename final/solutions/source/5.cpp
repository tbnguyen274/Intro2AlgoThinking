/*
BÀI 5: TÌM TẤT CẢ VỊ TRÍ XUẤT HIỆN CỦA XÂU B TRONG XÂU A

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- Xâu A (text)
- Xâu B (pattern)
- Độ dài A, B không quá 10^6

Output:
- Tất cả các vị trí i mà B xuất hiện trong A (vị trí đếm từ 1)
- Nếu không tìm thấy, bỏ trắng

Ví dụ: 
A = "aaaaa", B = "aa"
Các vị trí: 1, 2, 3, 4
- Vị trí 1: "aa" (A[0..1])
- Vị trí 2: "aa" (A[1..2])
- Vị trí 3: "aa" (A[2..3])
- Vị trí 4: "aa" (A[3..4])

===== CÁCH 1: BRUTE FORCE =====

Approach:
1. Duyệt qua từng vị trí i của A (từ 0 đến len(A) - len(B))
2. Tại mỗi vị trí i, so sánh B với substring A[i..i+len(B)-1]
3. Nếu khớp, lưu vị trí i+1 (vì đếm từ 1)

Độ phức tạp: O(n * m)
- n = len(A), m = len(B)
- Trong worst case: A = "aaaa...", B = "aaa...b"
  => Mỗi vị trí so sánh gần hết m ký tự mới fail

Đánh giá: Với n, m ≤ 10^6:
- Worst case: O(10^6 * 10^6) = 10^12 => QUÁ CHẬM!
- Tuy nhiên, trong practice, average case tốt hơn nhiều
- Nếu không có overlap pattern phức tạp, thường chạy nhanh

===== CÁCH 2: KMP ALGORITHM - TỐI ƯU =====

Knuth-Morris-Pratt Algorithm
Ý tưởng chính:
- Khi mismatch xảy ra, không quay lại từ đầu
- Sử dụng thông tin đã so sánh để skip các vị trí không cần thiết
- Preprocess pattern để tạo LPS array (Longest Proper Prefix which is also Suffix)

LPS Array:
- lps[i] = độ dài của proper prefix dài nhất của pattern[0..i] 
  mà cũng là suffix của pattern[0..i]

Ví dụ: B = "aaaa"
lps[] = [0, 1, 2, 3]

Ví dụ: B = "abab"
lps[] = [0, 0, 1, 2]

Độ phức tạp: O(n + m)
- Build LPS: O(m)
- Search: O(n)
- Space: O(m)

Với n, m ≤ 10^6: O(2 * 10^6) => Hoàn toàn OK!

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===== SOLUTION 1: BRUTE FORCE =====
vector<int> solution1_bruteforce(const string& A, const string& B) {
    vector<int> result;
    int n = A.length();
    int m = B.length();
    
    if (m > n) return result;
    
    // Duyệt qua từng vị trí có thể
    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        
        // So sánh B với substring A[i..i+m-1]
        for (int j = 0; j < m; j++) {
            if (A[i + j] != B[j]) {
                match = false;
                break;
            }
        }
        
        if (match) {
            result.push_back(i + 1); // Vị trí đếm từ 1
        }
    }
    
    return result;
}

// ===== SOLUTION 2: KMP ALGORITHM =====

// Build LPS (Longest Proper Prefix which is also Suffix) array
// Time: O(m)
vector<int> buildLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    
    int len = 0; // Độ dài của previous longest prefix suffix
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
                // Không tăng i, thử lại với len mới
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

// KMP Search
// Time: O(n)
vector<int> solution2_kmp(const string& A, const string& B) {
    vector<int> result;
    int n = A.length();
    int m = B.length();
    
    if (m > n) return result;
    if (m == 0) return result;
    
    // Build LPS array
    vector<int> lps = buildLPS(B);
    
    int i = 0; // Index cho A
    int j = 0; // Index cho B
    
    while (i < n) {
        if (A[i] == B[j]) {
            i++;
            j++;
        }
        
        if (j == m) {
            // Tìm thấy pattern tại vị trí i - j
            result.push_back(i - j + 1); // +1 vì đếm từ 1
            j = lps[j - 1];
        } else if (i < n && A[i] != B[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return result;
}

// ===== MAIN =====
int main() {
    string A, B;
    getline(cin, A);
    getline(cin, B);
    
    // Sử dụng KMP (optimal solution)
    vector<int> positions = solution2_kmp(A, B);
    
    // In kết quả
    for (int i = 0; i < positions.size(); i++) {
        if (i > 0) cout << " ";
        cout << positions[i];
    }
    if (!positions.empty()) {
        cout << endl;
    }
    
    return 0;
}

/*
===== TEST VÍ DỤ =====

Input:
aaaaa
aa

Process (KMP):
1. Build LPS cho "aa": [0, 1]
2. Search:
   - i=0, j=0: A[0]='a' == B[0]='a' => i=1, j=1
   - i=1, j=1: A[1]='a' == B[1]='a' => i=2, j=2
   - j==2 => Found at position 0 (output: 1)
   - j = lps[1] = 1 => j=1
   - i=2, j=1: A[2]='a' == B[1]='a' => i=3, j=2
   - j==2 => Found at position 1 (output: 2)
   - j = lps[1] = 1 => j=1
   - i=3, j=1: A[3]='a' == B[1]='a' => i=4, j=2
   - j==2 => Found at position 2 (output: 3)
   - j = lps[1] = 1 => j=1
   - i=4, j=1: A[4]='a' == B[1]='a' => i=5, j=2
   - j==2 => Found at position 3 (output: 4)

Output: 1 2 3 4

===== PHÂN TÍCH SO SÁNH =====

Test case worst cho Brute Force:
A = "aaaaaaaaa...aab" (n ký tự)
B = "aaa...aab" (m ký tự)
=> O(n * m) = 10^12 operations => TLE

Test case tốt cho Brute Force:
A = "abcdefghijk..."
B = "xyz"
=> Hầu hết vị trí fail ngay ký tự đầu => O(n) trong practice

KMP luôn đảm bảo O(n + m) trong mọi trường hợp!
*/
