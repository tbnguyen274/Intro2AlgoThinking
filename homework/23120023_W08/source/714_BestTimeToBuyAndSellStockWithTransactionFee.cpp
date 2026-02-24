/*
    Difficulty: Medium
    Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
*/

#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> buy(n, 0);
        vector<int> sell(n, 0);
        buy[0] -= prices[0];

        for (int i = 1; i < n; i++) {
            // find max -price -> minimize the price to buy
            // do nothing or buy previously sold stock
            buy[i] = max(buy[i - 1], sell[i - 1] - prices[i]);

            // do nothing or sell previously bought stock
            sell[i] = max(sell[i - 1], buy[i - 1] + prices[i] - fee);
        }

        return sell[n - 1];
    }
};