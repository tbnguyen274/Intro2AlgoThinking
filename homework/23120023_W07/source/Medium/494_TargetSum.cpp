/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/target-sum/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();

        int totalSum = 0;
        for (int x : nums) totalSum += x;

        if (abs(target) > totalSum) return 0;

        vector<int> dp(totalSum * 2 + 1, 0);
        dp[nums[0] + totalSum] = 1;
        dp[-nums[0] + totalSum] += 1;

        for (int i = 1; i < n; i++) {
            vector<int> nextState(totalSum * 2 + 1, 0);
            for (int sum = -totalSum; sum <= totalSum; sum++) {
                if (dp[sum + totalSum] > 0) {
                    nextState[sum + totalSum + nums[i]] += dp[sum + totalSum];
                    nextState[sum + totalSum - nums[i]] += dp[sum + totalSum];
                    
                }
            }
            dp = nextState;
        }

        return dp[target + totalSum];
    }
};