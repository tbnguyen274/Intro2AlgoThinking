/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/n-th-tribonacci-number/
*/

using namespace std;

class Solution {
public:
    int tribonacci(int n) {
        if (n < 2) return n;
        int a = 0, b = 1, c = 1;
        int next;

        for (int i = 3; i <= n; i++) {
            next = a + b + c;
            a = b;
            b = c;
            c = next;
        }

        return c;
    }
};