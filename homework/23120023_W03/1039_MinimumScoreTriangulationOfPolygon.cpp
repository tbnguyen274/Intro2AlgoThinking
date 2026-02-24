/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/minimum-score-triangulation-of-polygon/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(50, vector<int>(50, 0));

        // bottom - up dp
        // when triangulate the polygon, there will be 3 sub-polygons
        // by moving i backwards, we ensure to have processed the two small sub-polygon before calculating the minScore of the whole polygon

        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                if (!dp[i][j]) {
                    dp[i][j] = INT_MAX;
                }

                for (int k = i + 1; k < j; k++) {
                    int curScore = dp[i][k] + 
                                    values[i] * values[j] * values[k] + 
                                    dp[k][j];
                    
                    dp[i][j] = min(dp[i][j], curScore);
                }
            }
        }

        return dp[0][n - 1];


    }
};