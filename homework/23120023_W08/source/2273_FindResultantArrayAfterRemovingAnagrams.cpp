/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/
*/

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        int n = words.size();
        vector<string> ans(1, words[0]);

        for (int i = 1; i < n; i++) {
            string s1 = words[i], s2 = ans.back();

            sort(s1.begin(), s1.end());
            sort(s2.begin(), s2.end());

            if (s1 != s2) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
};