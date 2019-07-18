/*
Divide Two Integers

URL: https://leetcode.com/problems/divide-two-integers
Tags: ['math', 'binary-search']
___

Given two integers `dividend` and `divisor`, divide two integers without using
multiplication, division and mod operator.

Return the quotient after dividing `dividend` by `divisor`.

The integer division should truncate toward zero.

Example 1:

    Input: dividend = 10, divisor = 3
    Output: 3

Example 2:

    Input: dividend = 7, divisor = -3
    Output: -2

Note:

  * Both dividend and divisor will be 32-bit signed integers.
  * The divisor will never be 0.
  * Assume we are dealing with an environment which could only store integers
within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of
this problem, assume that your function returns 231 − 1 when the division result
overflows.
*/

#include <tuple>
#include <limits>
#include "catch.hpp"

using std::tuple;

namespace divide_two_integers {

namespace v1 {
// NOTE: 这个版本是不可用的, Time Limit Exceeded.
class Solution {
public:
    int divide(int dividend, int divisor) {
        bool s1 = true, s2 = true;
        if (dividend > 0) {
            s1 = false;
            dividend = -dividend;
        }
        if (divisor > 0) {
            s2 = false;
            divisor = -divisor;
        }
        int result = 0;
        for (;;) {
            dividend -= divisor;
            if (dividend <= 0) {
                result--;
            } else {
                break;
            }
        }
        if (s1 ^ s2) {
            return result;
        } else {
            if (result == std::numeric_limits<int>::min()) {
                return std::numeric_limits<int>::max();
            }
            return -result;
        }
    }
};
} // namespace v1

inline namespace v2 {
// v1 中由于一个一个减太慢, 所以 v2 就2倍2倍的减
// 这里主要有两个技巧:
// 1. 用 加法 + 递归 模拟出 累乘2
// 2. 用负数进行计算避免溢出产生的问题
// 另外: 题目中有明确要求只能使用 32 位有符号的整数类型,
// 所以我看到很多使用 long long 的答案都没有严格遵守这个要求.
class Solution {
public:
    int divide(int dividend, int divisor) {
        // 由于负数的范围大于正数, 所以用负数来计算更加方便.
        bool s1 = true, s2 = true;
        if (dividend > 0) {
            s1 = false;
            dividend = -dividend;
        }
        if (divisor > 0) {
            s2 = false;
            divisor = -divisor;
        }
        int result = 0;
        for (;;) {
            auto r = getMax(dividend, divisor, -1);
            if (std::get<2>(r)) {
                dividend -= std::get<0>(r);
                result += std::get<1>(r);
            } else {
                break;
            }
        }
        if (s1 ^ s2) {
            return result;
        } else {
            // 注意 -(负数最小值) 的值是不变的, 仍然是负数最小值,
            // 所以这里需要判断一下
            if (result == std::numeric_limits<int>::min()) {
                return std::numeric_limits<int>::max();
            }
            return -result;
        }
    }

private:
    // 输入均为负数
    tuple<int, int, bool> getMax(int dividend, int divisor, int n) {
        if (dividend > divisor) {
            return std::make_tuple(0, 0, false);
        }
        auto dd = divisor + divisor;
        if (dd < 0) { // 判断没有溢出
            auto r = getMax(dividend, dd, n + n);
            if (std::get<2>(r)) {
                return r;
            }
        }
        return std::make_tuple(divisor, n, true);
    }
};
} // namespace v2

TEST_CASE("Divide Two Integers") {
    Solution s;
    CHECK(s.divide(10, 3) == 3);
    CHECK(s.divide(7, -3) == -2);
    CHECK(s.divide(-2147483648, -1) == 2147483647);
    CHECK(s.divide(-2147483648, 1) == -2147483648);
}

} // namespace divide_two_integers
