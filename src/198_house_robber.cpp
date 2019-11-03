
/*
House Robber

URL: https://leetcode.com/problems/house-robber
Tags: ['dynamic-programming']
___

You are a professional robber planning to rob houses along a street. Each
house has a certain amount of money stashed, the only constraint stopping you
from robbing each of them is that adjacent houses have security system
connected and it will automatically contact the police if two adjacent houses
were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each
house, determine the maximum amount of money you can rob tonight without
alerting the police.

Example 1:

    Input: [1,2,3,1]
    Output: 4
    Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
                  Total amount you can rob = 1 + 3 = 4.

Example 2:

    Input: [2,7,9,3,1]
    Output: 12
    Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house
5 (money = 1). Total amount you can rob = 2 + 9 + 1 = 12.
*/

#include "test.h"

using std::vector;

namespace house_robber {

/*
    动态规划
    max(i) = max(
        max(i - 2) + nums[i], // 取 i
        max(i - 1), // 不取 i
    )
*/
inline namespace v1 {
using std::max;
class Solution {
public:
    int rob(vector<int>& nums) {
        int max0 = 0, max1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int n = max(max0 + nums[i], max1);
            max0 = max1;
            max1 = n;
        }
        return max1;
    }
};
} // namespace v1

TEST_CASE("House Robber") {
    TEST_SOLUTION(rob, v1) {
        vector<int> v = {1, 2, 3, 1};
        CHECK(rob(v) == 4);
        v = {2, 1, 1, 2};
        CHECK(rob(v) == 4);
    };
}

} // namespace house_robber
