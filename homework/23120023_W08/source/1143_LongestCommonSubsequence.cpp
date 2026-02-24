/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/longest-common-subsequence/
*/

#include <string>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int dp[1001][1001] = {0};
        int n = text1.size(), m = text2.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (text1[i] == text2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                } else {
                    dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }

        return dp[n][m];
    }
};