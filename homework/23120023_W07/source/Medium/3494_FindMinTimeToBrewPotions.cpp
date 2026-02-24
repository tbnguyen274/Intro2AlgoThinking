/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/
*/

#include <vector>

using namespace std;

class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();
        int m = mana.size();
        vector<long long> finish(n + 1);

        /*
            note:
            - finish: 1-indexed
            - skill: 0-indexed
            --> finish[i + 1] corresponds with skill[i]
                or finish[i] corresponds with skill[i - 1]
        */

        for (int j = 0; j < m; j++) {
            // 1-indexed wizards traversal
            for (int i = 1; i <= n; i++) {
                long long time = skill[i - 1] * mana[j];
                /*
                can work when:
                - current wizard has finished his last potion
                - directly previous wizard has finished his current potion
                to pass to the current wizard
                --> max(finish[i], finish[i - 1])
                */
                long long workable = max(finish[i], finish[i - 1]);
                finish[i] = workable + time;
            }

            for (int i = n - 1; i > 0; i--) {
                // reverse traversal to update the time each wizard finishes
                // prevFin = curFin - curTime
                finish[i] = finish[i + 1] - skill[i] * mana[j];

                // note: set condition i >= 0 in for loop to calculate the start time if needed
            }
        }

        // min time required for potions to be brewed properly is when the last wizard finishes his last potion
        return finish[n];
    }
};