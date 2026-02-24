/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 1)
            return 1;

        sort(points.begin(), points.end(),
             [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });

        int res = 1;
        int end = points[0][1];

        // Main idea explained by given example:
        // [1 6], [2 8], [7 12], [10 16]

        // the first arrow is between 1 and 6 (res = 1)

        // as [2 8] overlaps with [1 6], no more arrows needed
        // as we can choose an arrow like 2, 3, 4, ...

        // [7 12] is non-overlapping with [1 6], new arrow needed (res++)
        // reset the interval of new arrow: [7 12]

        // [10 16] overlaps with [7 12], no more arrows needed
        // as we can choose an arrow like 10, 11, 12.

        // so the minimum number of arrows is 2.

        // if the current arrow(s) unable to burst balloons in new interval

        for (int i = 1; i < n; i++) {
            if (points[i][0] > end) {
                res++;
                end = points[i][1];
            }
        }

        return res;
    }
};