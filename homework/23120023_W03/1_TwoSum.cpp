/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/two-sum/
*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mapNumIndex;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];

            if (mapNumIndex.find(diff) != mapNumIndex.end()) {
                return {i, mapNumIndex[diff]};
            }
            mapNumIndex[nums[i]] = i;
        }
        
        return {};
    }
};