/*
Reverse Integer

URL: https://leetcode.com/problems/reverse-integer
Tags: ['math']
___

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

    Input: 123
    Output: 321


Example 2:

    Input: -123
    Output: -321


Example 3:

    Input: 120
    Output: 21


Note:
Assume we are dealing with an environment which could only store integers
within the 32-bit signed integer range: [ −2^31,  2^31 − 1]. For the purpose of
this problem, assume that your function returns 0 when the reversed integer
overflows.
*/

#include "test.h"

using std::numeric_limits;

namespace reverse_integer {

inline namespace v1 {
class Solution {
    static const auto minHead = numeric_limits<int>::min() / 10;
    static const auto minTail = numeric_limits<int>::min() % 10;
    static const auto maxHead = numeric_limits<int>::max() / 10;
    static const auto maxTail = numeric_limits<int>::max() % 10;

public:
    int reverse(int x) {
        int result = 0;
        while (x != 0) {
            auto tail = x % 10;
            if (result <= minHead || result >= maxHead) {
                if (result == minHead) {
                    if (tail < minTail) {
                        return 0;
                    }
                } else if (result == maxHead) {
                    if (tail > maxTail) {
                        return 0;
                    }
                } else {
                    return 0;
                }
            }
            result = result * 10 + tail;
            x /= 10;
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Reverse Integer") {
    TEST_SOLUTION(reverse, v1) {
        CHECK(reverse(123) == 321);
        CHECK(reverse(-123) == -321);
        CHECK(reverse(120) == 21);
        CHECK(reverse(1534236469) == 0);

        BENCHMARK("") { return reverse(1534236469); };
    };
}

} // namespace reverse_integer
