/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/minimum-path-sum/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<int> dp(cols, 0);

        for (int i = 0; i < rows; i++) {
            dp[0] = dp[0] + grid[i][0];

            for (int j = 1; j < cols; j++) {
                if (i == 0) {
                    dp[j] = grid[i][j] + dp[j - 1];
                } else {
                    dp[j] = grid[i][j] + min(dp[j - 1], dp[j]);
                }
            }
        }

        return dp[cols - 1];
    }
};