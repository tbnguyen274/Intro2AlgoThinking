/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/compare-version-numbers/
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        // count number of dots
        int countDot1 = 0, countDot2 = 0;
        for (char c : version1) {
            if (c == '.') countDot1++;
        }

        for (char c : version2) {
            if (c == '.') countDot2++;
        }

        // create arrays to store numbers, if missing, filled by zero
        int maxDot = max(countDot1, countDot2);
        vector<int> arr1(maxDot + 1, 0), arr2(maxDot + 1, 0);
        string temp = "";
        int i = 0;

        for (char c : version1) {
            if (c != '.') {
                temp += c;
            }
            else {
                arr1[i++] = stoi(temp);
                temp = "";
            }
        }
        // last number
        arr1[i] = stoi(temp);

        // reset
        temp = "";
        i = 0;

        for (char c : version2) {
            if (c != '.') {
                temp += c;
            }
            else {
                arr2[i++] = stoi(temp);
                temp = "";
            }
        }
        // last number
        arr2[i] = stoi(temp);

        // traverse from left to right
        for (int i = 0; i < maxDot + 1; i++) {
            if (arr1[i] < arr2[i]) {
                return -1;
            }
            else if (arr1[i] > arr2[i]) {
                return 1;
            }
        }

        return 0;
    }
};