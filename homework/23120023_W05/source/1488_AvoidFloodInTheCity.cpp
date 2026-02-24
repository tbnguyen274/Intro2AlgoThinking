/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/avoid-flood-in-the-city/
*/

#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, 1);
        // <lake, day it was fulfilled>
        unordered_map<int, int> mpFull;
        set<int> drydays;

        for (int i = 0; i < n; i++) {
            // no rain on any lakes -> can dry a lake this day
            if (rains[i] == 0) {
                drydays.insert(i);
            } 
            else {
                // rain on this lake
                ans[i] = -1;
                int lake = rains[i];

                // not the first time -> can cause flood
                if (mpFull.find(lake) != mpFull.end()) {
                    // find nearest dry day after the last day it rained
                    auto it = drydays.lower_bound(mpFull[lake]);

                    // can't find day to dry -> flood is inevitable
                    if (it == drydays.end()) {
                        return {};
                    }

                    // dry day found -> dry current lake on that day
                    int dryday = *it;
                    ans[dryday] = lake;

                    // erase the dry day that has been used
                    drydays.erase(dryday);
                }
                
                // upddate the latest day it rains on this lake
                mpFull[lake] = i;
            }
        }

        return ans;
    }
};