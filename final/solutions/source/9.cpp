/*
BÀI 9: REGULAR EXPRESSION MATCHING

===== PHÂN TÍCH BÀI TOÁN =====

Input: 
- Chuỗi s (text)
- Chuỗi p (pattern) với các ký tự đặc biệt:
  + '*': Khớp với 0 hoặc nhiều lần ký tự ngay trước đó
  + '.': Khớp với chính xác 1 ký tự bất kỳ

Output:
- "true" nếu s khớp với pattern p
- "false" nếu không khớp

Ví dụ:
1. s = "aab", p = "c*a*b"
   - "c*" => 0 lần 'c' => ""
   - "a*" => 2 lần 'a' => "aa"
   - "b" => "b"
   => Tạo ra "aab" => true

2. s = "mississippi", p = "mis*is*p*."
   - "mi" => "mi"
   - "s*" => 1 lần 's' => "s"
   - "is*" => Cần khớp với "sissippi"
   => Không thể khớp => false

===== CÁCH 1: RECURSION - Ý TƯỞNG ĐƠN GIẢN =====

Approach:
1. Base cases:
   - Nếu pattern rỗng: return (text rỗng)
   - Nếu text rỗng: kiểm tra pattern có thể tạo ra rỗng không (các cặp x*)

2. Check khớp ký tự đầu:
   - first_match = (text[0] == pattern[0]) hoặc (pattern[0] == '.')

3. Xử lý '*':
   - Nếu pattern[1] == '*':
     + Option 1: Dùng '*' khớp 0 lần => Skip pattern[0] và '*'
     + Option 2: Dùng '*' khớp ≥1 lần => first_match và tiếp tục với text[1..]
   
   - Nếu không có '*':
     + first_match và tiếp tục với text[1..] và pattern[1..]

Độ phức tạp: 
- Time: O(2^(n+m)) trong worst case (exponential)
- Space: O(n+m) cho recursion stack

Với len(s) ≤ 20, len(p) ≤ 30:
- Worst: 2^50 ≈ 10^15 => QUÁ CHẬM!

===== CÁCH 2: DYNAMIC PROGRAMMING - TỐI ƯU =====

Ý tưởng:
- Có nhiều subproblems bị tính lại trong recursion
- Dùng memoization hoặc DP table

DP Definition:
- dp[i][j] = true nếu s[0..i-1] khớp với p[0..j-1]
- dp[0][0] = true (chuỗi rỗng khớp với pattern rỗng)

Base cases:
- dp[0][0] = true
- dp[0][j] = true nếu p[0..j-1] có thể tạo ra rỗng (các cặp x*)
- dp[i][0] = false nếu i > 0 (text không rỗng không khớp với pattern rỗng)

Transition:
1. Nếu p[j-1] != '*':
   - dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.')

2. Nếu p[j-1] == '*':
   - Option 1: Khớp 0 lần => dp[i][j] = dp[i][j-2]
   - Option 2: Khớp ≥1 lần => dp[i][j] = dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.')
   - dp[i][j] = Option1 OR Option2

Độ phức tạp:
- Time: O(n * m)
- Space: O(n * m)

Với n ≤ 20, m ≤ 30:
- O(20 * 30) = 600 operations => Hoàn toàn OK!

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===== SOLUTION 1: RECURSION =====
bool isMatchRecursive(const string& s, const string& p, int i, int j) {
    // Base case: pattern rỗng
    if (j == p.length()) {
        return i == s.length();
    }
    
    // Check khớp ký tự đầu
    bool first_match = (i < s.length() && 
                       (s[i] == p[j] || p[j] == '.'));
    
    // Xử lý '*'
    if (j + 1 < p.length() && p[j + 1] == '*') {
        // Option 1: Khớp 0 lần (skip pattern[j] và '*')
        // Option 2: Khớp ≥1 lần (dùng first_match và tiếp tục với text[i+1])
        return isMatchRecursive(s, p, i, j + 2) ||
               (first_match && isMatchRecursive(s, p, i + 1, j));
    } else {
        // Không có '*': phải khớp first_match và tiếp tục
        return first_match && isMatchRecursive(s, p, i + 1, j + 1);
    }
}

bool solution1_recursion(const string& s, const string& p) {
    return isMatchRecursive(s, p, 0, 0);
}

// ===== SOLUTION 2: DP WITH MEMOIZATION =====
bool isMatchMemo(const string& s, const string& p, int i, int j, 
                 vector<vector<int>>& memo) {
    // Đã tính trước
    if (memo[i][j] != -1) {
        return memo[i][j];
    }
    
    bool result;
    
    // Base case
    if (j == p.length()) {
        result = (i == s.length());
    } else {
        bool first_match = (i < s.length() && 
                           (s[i] == p[j] || p[j] == '.'));
        
        if (j + 1 < p.length() && p[j + 1] == '*') {
            result = isMatchMemo(s, p, i, j + 2, memo) ||
                    (first_match && isMatchMemo(s, p, i + 1, j, memo));
        } else {
            result = first_match && isMatchMemo(s, p, i + 1, j + 1, memo);
        }
    }
    
    memo[i][j] = result;
    return result;
}

bool solution2_memoization(const string& s, const string& p) {
    int n = s.length();
    int m = p.length();
    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    return isMatchMemo(s, p, 0, 0, memo);
}

// ===== SOLUTION 3: DP TABLE (BOTTOM-UP) =====
bool solution3_dp(const string& s, const string& p) {
    int n = s.length();
    int m = p.length();
    
    // dp[i][j] = s[0..i-1] khớp với p[0..j-1]
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    
    // Base case: chuỗi rỗng khớp với pattern rỗng
    dp[0][0] = true;
    
    // Pattern có thể tạo ra chuỗi rỗng (các cặp x*)
    for (int j = 2; j <= m; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }
    
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                // '*' khớp với 0 lần ký tự trước đó
                dp[i][j] = dp[i][j - 2];
                
                // '*' khớp với ≥1 lần ký tự trước đó
                if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            } else {
                // Khớp ký tự hiện tại
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
    }
    
    return dp[n][m];
}

// ===== MAIN =====
int main() {
    string s, p;
    getline(cin, s);
    getline(cin, p);
    
    // Sử dụng DP (optimal solution)
    bool result = solution3_dp(s, p);
    
    cout << (result ? "true" : "false") << endl;
    
    return 0;
}

/*
===== TEST VÍ DỤ =====

Test 1: s = "aab", p = "c*a*b"

DP Table:
    ""  c  c* a  a* b
""  T   F  T  F  T  F
a   F   F  F  T  T  F
a   F   F  F  F  T  F
b   F   F  F  F  F  T

dp[3][5] = true

Giải thích:
- "" khớp với "c*" (0 lần 'c')
- "aa" khớp với "c*a*" (0 lần 'c', 2 lần 'a')
- "aab" khớp với "c*a*b" (0 lần 'c', 2 lần 'a', 1 lần 'b')

Test 2: s = "mississippi", p = "mis*is*p*."

DP Table (simplified):
Pattern "mis*is*p*." cố gắng khớp "mississippi"
- "mi" khớp với "mi"
- "s*" khớp với "ss" (2 lần 's')
- "is*" khớp với "i" (0 lần 's')
- Còn lại "ssissippi" không thể khớp với "p*."

dp[11][10] = false

===== KEY INSIGHTS =====

1. '*' luôn đi kèm với ký tự trước đó (xử lý theo cặp)
2. '*' có thể khớp 0, 1, hoặc nhiều lần
3. '.' chỉ khớp chính xác 1 ký tự
4. DP giúp tránh tính lại subproblems

===== EDGE CASES =====

1. s = "", p = "a*b*c*" => true (tất cả khớp 0 lần)
2. s = "a", p = "ab*" => true ("b*" khớp 0 lần)
3. s = "aaa", p = "a*a" => true ("a*" khớp 2 lần, "a" khớp 1 lần)
4. s = "ab", p = ".*" => true (".*" khớp toàn bộ)
*/
