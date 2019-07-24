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
within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of
this problem, assume that your function returns 2^31 − 1 when the division
result overflows.
*/

#include <tuple>
#include <limits>
#include "test.h"

using std::tuple;

namespace divide_two_integers {

namespace v1 {
/*
NOTE: 这个版本是不可用的, Time Limit Exceeded.

主要有思路就是: 用减法迭代来模拟除法.

另外, 还有个技巧就是用负数进行计算, 避免溢出产生的问题
(题目中明确要求只能使用32位有符号的整数类型, 使用 long long 是犯规的).
*/
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
/*
v1 中由于一个一个减太慢, 所以 v2 就2倍2倍的减.
主要的技巧是用`加法` + `递归`模拟出`累乘2`.
*/
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
    TEST_SOLUTION(divide, v1, v2) {
        CHECK(divide(10, 3) == 3);
        CHECK(divide(7, -3) == -2);
        CHECK(divide(-2147483648, -1) == 2147483647);
        CHECK(divide(-2147483648, 1) == -2147483648);

        BENCHMARK("") { return divide(-2147483648, -1); };
    };
}

} // namespace divide_two_integers
