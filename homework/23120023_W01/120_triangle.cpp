/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/triangle/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // bottom-up dynamic programming

        int n = triangle.size();
        
        // firstly, insert the bottom-most level as the starting values
        vector<int> minPath(triangle.back());

        // traverse each level upwards
        for (int level = n - 2; level >= 0; level--) { 
            // go through all numbers on the current level
            for (int i = 0; i <= level; i++) {  
                // update minPath[i] (min path to the current number)
                // = the smaller of the two children of current number + the number itself
                minPath[i] = min(minPath[i], minPath[i + 1]) + triangle[level][i];
            }
        }

        // in the end, minPath[0] is the min path sum after reaching the top
        return minPath[0];
    }
};