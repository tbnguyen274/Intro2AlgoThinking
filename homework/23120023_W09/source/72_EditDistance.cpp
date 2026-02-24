/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/edit-distance/
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();

        // dp[i][j] = min operations to change word1[0..i] to word2[0..j]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        // delete all i characters from word1
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        // insert all j characters to form word2
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j - 1],   // Replace: change word1[i-1] to word2[j-1]
                        dp[i - 1][j],       // Delete: remove word1[i-1]
                        dp[i][j - 1]});     // Insert: add word2[j-1]
                }
            }
        }

        return dp[m][n];
    }
};