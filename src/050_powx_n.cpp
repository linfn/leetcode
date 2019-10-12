
/*
Pow(x, n)

URL: https://leetcode.com/problems/powx-n
Tags: ['math', 'binary-search']
___

Implement [pow( x , n )](http://www.cplusplus.com/reference/valarray/pow/),
which calculates  x raised to the power n (x n).

Example 1:

    Input: 2.00000, 10
    Output: 1024.00000


Example 2:

    Input: 2.10000, 3
    Output: 9.26100


Example 3:

    Input: 2.00000, -2
    Output: 0.25000
    Explanation: 2 -2 = 1/22 = 1/4 = 0.25


Note:

  * -100.0 < x < 100.0
  * n is a 32-bit signed integer, within the range  [−231, 231 − 1]
*/

#include "test.h"

namespace powx_n {

inline namespace v1 {
class Solution {
public:
    double myPow(double x, int n) {
        double result = 1;
        long long m = n;
        if (m < 0) {
            m = -m;
        }
        while (m > 0) {
            double r = x;
            long long k = 1;
            while (m >= k * 2) {
                r *= r;
                k *= 2;
            }
            result *= r;
            m -= k;
        }
        if (n > 0) {
            return result;
        }
        return 1 / result;
    }
};
} // namespace v1

TEST_CASE("Pow(x, n)") {
    TEST_SOLUTION(myPow, v1) {
        CHECK(myPow(2, 10) == 1024.00000);
        CHECK(myPow(2, 18) == 262144.00000);
        CHECK(myPow(2, 0) == 1);
        CHECK(myPow(2, -2) == 0.25000);
    };
}

} // namespace powx_n
