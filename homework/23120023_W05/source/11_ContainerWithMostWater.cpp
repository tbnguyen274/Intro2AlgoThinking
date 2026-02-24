/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/container-with-most-water/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int l = 0, r = height.size() - 1;

        while (l < r) {
            int w = r - l;
            int h = min(height[l], height[r]);
            int area = w * h;
            maxArea = max(maxArea, area);

            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }
        
        return maxArea;
    }
};