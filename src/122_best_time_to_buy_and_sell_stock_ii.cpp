
/*
Best Time to Buy and Sell Stock II

URL: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii
Tags: ['array', 'greedy']
___

Say you have an array for which the i th element is the price of a given stock
on day i.

Design an algorithm to find the maximum profit. You may complete as many
transactions as you like (i.e., buy one and sell one share of the stock
multiple times).

Note: You may not engage in multiple transactions at the same time (i.e., you
must sell the stock before you buy again).

Example 1:

    Input: [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit
= 5-1 = 4. Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit =
6-3 = 3.


Example 2:

    Input: [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit
= 5-1 = 4. Note that you cannot buy on day 1, buy on day 2 and sell them later,
as you are engaging multiple transactions at the same time. You must sell before
buying again.


Example 3:

    Input: [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include "test.h"

using std::max;
using std::vector;

namespace best_time_to_buy_and_sell_stock_ii {

inline namespace v1 {
/*
我的思路是如果到第 i 天为止的最优解是已知的, 那增加第 i+1 天时会发生什么?
结果真的意外的简单.
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); i++) {
            result += max(prices[i] - prices[i - 1], 0);
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Best Time to Buy and Sell Stock II") {
    TEST_SOLUTION(maxProfit, v1) {
        vector<int> v = {7, 1, 5, 3, 6, 4};
        CHECK(maxProfit(v) == 7);
        v = {1, 2, 3, 4, 5};
        CHECK(maxProfit(v) == 4);
        v = {7, 6, 4, 3, 1};
        CHECK(maxProfit(v) == 0);

        v = {7, 6, 4, 3, 1};
        BENCHMARK("") { return maxProfit(v); };
    };
}

} // namespace best_time_to_buy_and_sell_stock_ii
