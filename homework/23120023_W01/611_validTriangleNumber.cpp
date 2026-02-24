/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/valid-triangle-number/
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        
        // traverse from right to left
        for (int i = n - 1; i >= 1; i--) {
            int left = 0;
            int right = i - 1;  // next to current number to the left (smaller)

            // find left and right bound so that nums[left] + nums[right] > current number <=> a + b > c
            // if not, keep incrementing left
            while (left < right) {
                if (nums[left] + nums[right] <= nums[i]) {
                    left++;
                }
                else {
                    // all numbers larger than nums[left] can make a pair with nums[right] to form a valid triangle
                    ans += right - left;
                    right -= 1;
                }
            }
        }

        return ans;

    }
};