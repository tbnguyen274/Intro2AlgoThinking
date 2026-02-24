/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/
*/

class Solution {
public:
    bool checkPowersOfThree(int n) {
        
        // Base 3 representation: X = a_0.3^0 + a_1.3^1 + a_2.3^2 + ...

        // if any a_i equals to 2, it violates the rule of DISTINCT powers
        // which means a_i can only be 0 or 1.

        // Ex: 2.3^2 = 3^2 + 3^2 ---> not distinct

        while (n > 0) {
            if (n % 3 == 2) return false;
            n /= 3;
        }

        return true;
    }
};