/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/koko-eating-bananas/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        int maxCount = piles[0];

        for (int i = 1; i < n; i++) {
            maxCount = max(maxCount, piles[i]);
        }

        int left = 1, right = maxCount;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long time = 0;

            // calculate time to eat all bananas
            for (int i = 0; i < n; i++) {
                time += ((piles[i] - 1) / mid) + 1;
            }

            // if speed (bananas/h) still low -> search to the right
            if (time > h) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left; // min speed satisfying requirement
    }
};