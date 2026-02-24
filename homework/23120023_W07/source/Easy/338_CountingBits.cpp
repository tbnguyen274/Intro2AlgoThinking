/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/counting-bits/
*/

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1);
        ans[0] = 0;

        for (int i = 1; i <= n; ++i) {
            ans[i] = ans[i >> 1] + i % 2;
        }

        return ans;
    }
};