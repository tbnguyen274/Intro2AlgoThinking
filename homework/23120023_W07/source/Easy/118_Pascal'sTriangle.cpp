/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/pascals-triangle/
*/

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;

        for (int i = 0; i < numRows; i++) {
            vector<int> curRow(i + 1, 1);

            for (int j = 1; j < i; j++) {
                // sum of two directly above numbers
                curRow[j] = ans[i - 1][j - 1] + ans[i - 1][j];
            }

            ans.push_back(curRow);
        }

        return ans;
    }
};