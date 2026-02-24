/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/water-bottles/
*/

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int numEmpty = numBottles;
        int numNew, numLeft;
        
        while (numEmpty >= numExchange) {
            numNew = numEmpty / numExchange;
            numLeft = numEmpty % numExchange;
            numBottles += numNew;
            numEmpty = numNew + numLeft;
        }

        return numBottles;
    }
};