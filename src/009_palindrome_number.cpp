/*
Palindrome Number

URL: https://leetcode.com/problems/palindrome-number
Tags: ['math']
___

Determine whether an integer is a palindrome. An integer is a palindrome when
it reads the same backward as forward.

Example 1:

    Input: 121
    Output: true


Example 2:

    Input: -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it
becomes 121-. Therefore it is not a palindrome.


Example 3:

    Input: 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is not a palindrome.


Follow up:

Coud you solve it without converting the integer to a string?
*/

#include "test.h"

namespace palindrome_number {

inline namespace v1 {
/*
思路是先把数倒过来, 再判断是否和原始的数相等.

时间复杂度是 O(log10(n)), 因为迭代时每一次除 10
*/
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        int ori = x;
        int reverse = 0;
        while (x != 0) {
            reverse = reverse * 10 + x % 10;
            x /= 10;
        }
        return reverse == ori;
    }
};
} // namespace v1

TEST_CASE("Palindrome Number") {
    TEST_SOLUTION(isPalindrome, v1) {
        CHECK(isPalindrome(121) == true);
        CHECK(isPalindrome(-121) == false);
        CHECK(isPalindrome(10) == false);
        CHECK(isPalindrome(0) == true);
        CHECK(isPalindrome(21120) == false);

        BENCHMARK("") { return isPalindrome(21120); };
    };
}

} // namespace palindrome_number
