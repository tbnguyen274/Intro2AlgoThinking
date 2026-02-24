/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/zigzag-conversion/
*/

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1 || numRows > s.length()) {
            return s;
        }
        vector<string> lines(numRows, "");
        string res = "";
        int row = 0;
        int down = -1;

        for (int i = 0; i < s.length(); i++) {
            if (row == numRows - 1 || row == 0) {
                down *= -1;
            }
            lines[row] += s[i];
            if (down == 1) {
                row++;
            }
            else row--;
        }
        
        for (int i = 0; i < numRows; i++) {
            res += lines[i];
        }

        return res;
    }
};