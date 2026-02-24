/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/make-array-elements-equal-to-zero/
*/

#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();
        int leftSum = 0;
        int rightSum = accumulate(nums.begin(), nums.end(), 0);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                leftSum += nums[i];
                rightSum -= nums[i];
            }
            else {
                if (leftSum == rightSum) {
                    ans += 2;
                }
                if (abs(rightSum - leftSum) == 1) {
                    ++ans;
                }
            }
        }

        return ans;
    }
};