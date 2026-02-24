/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/number-of-laser-beams-in-a-bank/
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int countDevices(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '1') {
                ++count;
            }
        }
        return count;
    }

    int numberOfBeams(vector<string>& bank) {
        int n = bank.size();
        int ans = 0;
        int prevDevices = 0;
        int curDevices;

        for (int i = 0; i < n; i++) {
            curDevices = countDevices(bank[i]);
            if (!curDevices) continue;
            if (!prevDevices) {
                prevDevices = curDevices;
                continue;
            }

            ans += prevDevices * curDevices;
            prevDevices = curDevices;
        }

        return ans;
    }
};