/*
    Difficulty: Hard
    Source: https://leetcode.com/problems/median-of-two-sorted-arrays/
*/

#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int i = 0, j = 0;
        vector<int> ans;

        while (i < n1 && j < n2) {
            if (nums1[i] < nums2[j]) {
                ans.push_back(nums1[i]);
                i++;
            } else {
                ans.push_back(nums2[j]);
                j++;
            }
        }

        while (i < n1) {
            ans.push_back(nums1[i]);
            i++;
        }
        while (j < n2) {
            ans.push_back(nums2[j]);
            j++;
        }

        int n = ans.size();
        if (n % 2) {
            return 1.0 * ans[n / 2];
        } else {
            return (ans[n / 2] + ans[n / 2 - 1]) / 2.0;
        }

        return 0.0;
    }
};