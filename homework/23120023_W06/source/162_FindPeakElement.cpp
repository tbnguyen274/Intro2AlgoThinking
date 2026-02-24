/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/find-peak-element/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();

        // quick check
        if (n == 1) return 0;
        if (nums[0] > nums[1]) return 0;
        if (nums[n - 1] > nums[n - 2]) return n - 1;

        int left = 1, right = n - 2;
        int mid = -1;

        while (left <= right) {
            mid = left + (right - left) / 2;

            if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
                return mid;
            }
            // downward -> search left
            else if (nums[mid - 1] > nums[mid]) {
                right = mid - 1;
            }
            // upward -> search right
            else if (nums[mid + 1] > nums[mid]) {
                left =  mid + 1;
            }
        }

        return mid;
    
    }
};