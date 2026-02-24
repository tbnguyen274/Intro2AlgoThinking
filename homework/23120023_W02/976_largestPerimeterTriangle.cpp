/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/largest-perimeter-triangle/
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        // sorting approach
        
        // idea: for a <= b <= c, 
        // the requirement to form a valid triangle is a + b > c
        // c + a > b & c + b > a are obvious as c is the largest

        int n = nums.size();
        sort(nums.begin(), nums.end());

        // traverse backwards from the end to get the possible largest P
        for (int i = n - 1; i >= 2; i--) {
            if (nums[i - 2] + nums[i - 1] > nums[i]) {
                return nums[i] + nums[i - 1] + nums[i - 2];
            }
        }

        return 0;
    }
};