
/*
Valid Palindrome

URL: https://leetcode.com/problems/valid-palindrome
Tags: ['two-pointers', 'string']
___

Given a string, determine if it is a palindrome, considering only alphanumeric
characters and ignoring cases.

Note:  For the purpose of this problem, we define empty string as valid
palindrome.

Example 1:

    Input:  "A man, a plan, a canal: Panama"
    Output: true
    

Example 2:

    Input:  "race a car"
    Output: false
*/

#include "test.h"

namespace valid_palindrome {

inline namespace v1 {
class Solution {
public:
    bool isPalindrome(string s) {
        auto isAlphanumeric = [](char c) {
            return ('A' <= c  && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9');
        };
        for (int i = 0, j = s.length() - 1; ; i++, j--) {
            while(!isAlphanumeric(s[i]) && i < j) {
                i++;
            }
            while(!isAlphanumeric(s[j]) && i < j) {
                j--;
            }
            if (i >= j) {
                break;
            }
            if (tolower(s[i]) != tolower(s[j])) {
                return false;
            }
        }
        return true;
    }
};
} // namespace v1

TEST_CASE("Valid Palindrome") {
    TEST_SOLUTION(isPalindrome, v1) {
        CHECK(isPalindrome("A man, a plan, a canal: Panama"));
        CHECK_FALSE(isPalindrome("0P"));
        CHECK_FALSE(isPalindrome("race a car"));
    };
}

} // namespace valid_palindrome
