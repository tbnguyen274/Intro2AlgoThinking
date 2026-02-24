/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        int n = queries.size();
        vector<int> res;

        // colorMap: num of distinct colors
        // ballMap: color of the balls
        unordered_map<int, int> colorMap, ballMap;
        
        for (int i = 0; i < n; i++) {
            int ball = queries[i][0], color = queries[i][1];

            // check if this ball was already colored
            if (ballMap.find(ball) != ballMap.end()) {
                int prevColor = ballMap[ball];

                /*
                if (prevColor == color) {
                    // update the result array and move to next query
                    res.push_back(colorMap.size());
                    continue;
                }
                */

                // first subtract the number of this color in all balls traversed
                // if no balls are colored with this color, remove it
                if(--colorMap[prevColor] == 0) {
                    colorMap.erase(prevColor);
                }
            }

            ballMap[ball] = color;  // update new color
            colorMap[color]++;      // increase color count

            // add current num of distint colors to result array
            res.push_back(colorMap.size());     
        }

        return res;
    }
};