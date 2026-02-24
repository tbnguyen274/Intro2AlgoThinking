/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/water-bottles-ii/
*/

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int numFull = 0;
        int numEmpty = numBottles;

        while (numFull != 0 || numEmpty >= numExchange) {
            while (numEmpty >= numExchange) {
                numEmpty -= numExchange;
                numExchange++;
                numFull++;
            }

            numBottles += numFull;
            numEmpty += numFull;
            numFull = 0;
        }

        return numBottles;
    }
};