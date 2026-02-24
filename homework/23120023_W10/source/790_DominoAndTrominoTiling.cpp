/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/domino-and-tromino-tiling/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1e9 + 7;
        vector<long> dp(n + 4);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        for (int i = 4; i <= n; i++) {
            /*
                dp[i] = dp[i - 1] + dp[i - 2] + 2 * (dp[i - 3] + ... + dp[0])
                dp[i - 1] = dp[i - 2] + dp[i - 3] + 2 * (dp[i - 4] + ... + dp[0])
                -> dp[i] - dp[i - 1] = dp[i - 1] + dp[i - 3]
                -> dp[i] = 2dp[i - 1] + dp[i - 3]
            */
            dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
        }

        return dp[n];
    }
};