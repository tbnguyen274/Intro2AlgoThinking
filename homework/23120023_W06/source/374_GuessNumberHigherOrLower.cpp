/*
    Difficulty: Easy
    Source: https://leetcode.com/problems/guess-number-higher-or-lower/
*/

#include <vector>

using namespace std;

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int left = 0, right = n;
        int mid;

        while (left <= right) {
            mid = left + (right - left) / 2;
            int check = guess(mid);

            if (check == 1) {
                left = mid + 1;
            }
            else if (check == -1) {
                right = mid - 1;
            }
            else return mid;
        }

        return mid;
    }
};