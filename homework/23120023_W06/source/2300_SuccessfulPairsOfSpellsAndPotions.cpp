/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int numSpells = spells.size();
        int numPotions = potions.size();

        vector<int> pairs(numSpells, 0);

        // sort potions
        sort(potions.begin(), potions.end());

        // binary search
        for (int i = 0; i < numSpells; i++) {
            int left = 0, right = numPotions - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                long long curProduct = 1LL * spells[i] * potions[mid];

                if (curProduct >= success) {
                    right = mid - 1;
                }
                else left = mid + 1;
            }

            pairs[i] = numPotions - left;
        }

        return pairs;
    }
};