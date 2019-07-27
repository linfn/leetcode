
/*
Best Time to Buy and Sell Stock

URL: https://leetcode.com/problems/best-time-to-buy-and-sell-stock
Tags: ['array', 'dynamic-programming']
___

Say you have an array for which the i th element is the price of a given stock
on day i.

If you were only permitted to complete at most one transaction (i.e., buy one
and sell one share of the stock), design an algorithm to find the maximum
profit.

Note that you cannot sell a stock before you buy one.

Example 1:

    Input: [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit
= 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than buying price.


Example 2:

    Input: [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include <vector>

#include "test.h"

using std::vector;

namespace best_time_to_buy_and_sell_stock {

namespace v1 {
/*
蛮力解法, 需要注意的是可以当天买当天卖, 所以最小值是 0.
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;
        for (int i = 0; i < prices.size(); i++) {
            for (int j = i; j < prices.size(); j++) {
                int profit = prices[j] - prices[i];
                if (profit > max) {
                    max = profit;
                }
            }
        }
        return max;
    }
};
} // namespace v1

inline namespace v2 {
/*
动态规划:
设 `F[i]` 为第 `i` 天卖出获取到最大利益而买入的那天.

1. 如果 `prices[i]` 比 `prices[F[i-1]]` 要高, 则 `F[i] = F[i-1]`
2. 否则, `F[i] = i` (当天买当天卖)
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max = 0;
        int dp = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] <= prices[dp]) {
                dp = i;
            }
            int profit = prices[i] - prices[dp];
            if (profit > max) {
                max = profit;
            }
        }
        return max;
    }
};
} // namespace v2

TEST_CASE("Best Time to Buy and Sell Stock") {
    TEST_SOLUTION(maxProfit, v1, v2) {
        vector<int> v = {7, 1, 5, 3, 6, 4};
        CHECK(maxProfit(v) == 5);
        v = {7, 6, 4, 3, 1};
        CHECK(maxProfit(v) == 0);

        v = {7, 6, 4, 3, 1};
        BENCHMARK("") { return maxProfit(v); };
    };
}

} // namespace best_time_to_buy_and_sell_stock
