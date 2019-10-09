
/*
Climbing Stairs

URL: https://leetcode.com/problems/climbing-stairs
Tags: ['dynamic-programming']
___

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?

Note: Given n will be a positive integer.

Example 1:

    Input: 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps


Example 2:

    Input: 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1. 1 step + 1 step + 1 step
    2. 1 step + 2 steps
    3. 2 steps + 1 step
*/

#include "test.h"

using std::vector;

namespace climbing_stairs {

/*
    climbStairs(n) =
        climbStairs(n-1) 第一步走 1 的情况 + climbStairs(n-2) 第一步走 2 的情况
*/
inline namespace v1 {
class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        vector<int> cache(n);
        cache[0] = 1;
        cache[1] = 2;
        for (int i = 2; i < n; i++) {
            cache[i] = cache[i - 1] + cache[i - 2];
        }
        return cache.back();
    }
};
} // namespace v1

TEST_CASE("Climbing Stairs") {
    TEST_SOLUTION(climbStairs, v1) {
        CHECK(climbStairs(2) == 2);
        CHECK(climbStairs(3) == 3);
        CHECK(climbStairs(1) == 1);
        CHECK(climbStairs(34) == 9227465);
    };
}

} // namespace climbing_stairs
