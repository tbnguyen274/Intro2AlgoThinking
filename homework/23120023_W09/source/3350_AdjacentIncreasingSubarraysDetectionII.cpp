/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        int curLen = 1, prevLen = 0, maxLen = 0;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                curLen++;
            } else {
                prevLen = curLen;
                curLen = 1;
            }

            maxLen = max(maxLen, max(curLen / 2, min(prevLen, curLen)));
        }

        return maxLen;
    }
};