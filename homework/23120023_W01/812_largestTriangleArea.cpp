/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/largest-triangle-area/
*/

#include <vector>
#include <cstdlib>

using namespace std;

class Solution {
public:
    double calcArea(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
        // set p1 to be the centre
        int x1 = p1[0] - p2[0];
        int x2 = p1[0] - p3[0];
        int y1 = p1[1] - p2[1];
        int y2 = p1[1] - p3[1];

        return abs(x1 * y2 - x2 * y1);
    }

    double largestTriangleArea(vector<vector<int>>& points) {
        // vector cross product

        int maxArea = 0;
        int n = points.size();

        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    int curArea = calcArea(points[i], points[j], points[k]);
                    maxArea = max(maxArea, curArea);
                }
            }
        }

        return maxArea / 2.0;   // triangle
    }
};