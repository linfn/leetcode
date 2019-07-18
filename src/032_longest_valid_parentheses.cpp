/*
Longest Valid Parentheses

URL: https://leetcode.com/problems/longest-valid-parentheses
Tags: ['string', 'dynamic-programming']
___

Given a string containing just the characters `'('` and `')'`, find the length
of the longest valid (well-formed) parentheses substring.

Example 1:

    Input:  "(()"
    Output: 2
    Explanation: The longest valid parentheses substring is "()"


Example 2:

    Input:  ")()())"
    Output: 4
    Explanation: The longest valid parentheses substring is "()()"
*/

#include <string>
#include <vector>
#include "catch.hpp"

using std::string;
using std::vector;

namespace longest_valid_parentheses {

namespace v1 {
class Solution {
public:
    int longestValidParentheses(string s) {
        int max = 0;
        for (int i = 0; i < s.length(); i++) {
            auto cnt = longest(s, i);
            if (cnt > max) {
                max = cnt;
            }
        }
        return max;
    }

private:
    int longest(string s, int i) {
        int cnt = 0, sum = 0, cur = 0;
        for (; i < s.length(); i++) {
            int c = s[i] == '(' ? 1 : -1;
            if (sum + c < 0) {
                break;
            }
            sum += c;
            cur++;
            if (sum == 0) {
                cnt = cur;
            }
        }
        return cnt;
    }
};
} // namespace v1

inline namespace v2 {
/*
设 dp[i] 表示以 s[i] 为结尾的最长配对的长度.
显然, 对于 s[i] == '(' 的情况, dp[i] = 0.
对于 s[i] == ')' 情况:
1. 当 s[i-1] == '(' 时: dp[i] = dp[i-2] + 2.
2. 当 s[i-1] == ')' 时:
    1. 当 s[i-dp[i-1]-1] == '(' 时, 即 ...((....)) 形式,
    则 dp[i] = dp[i-1] + dp[i-dp[i-1]-2] + 2.
    2. 否则, dp[i] = 0.
*/
class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> vdp(s.size(), 0);
        auto dp = [&vdp](int i) { return i < 0 ? 0 : vdp[i]; };
        auto ss = [&s](int i) { return i < 0 ? '_' : s[i]; };
        int result = 0;
        for (int i = 1; i < s.length(); i++) {
            if (ss(i) == ')') {
                if (ss(i - 1) == '(') {
                    vdp[i] = dp(i - 2) + 2;
                } else {
                    if (ss(i - dp(i - 1) - 1) == '(') {
                        vdp[i] = dp(i - 1) + dp(i - dp(i - 1) - 2) + 2;
                    }
                }
            }
            if (dp(i) > result) {
                result = dp(i);
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Longest Valid Parentheses") {
    Solution s;
    CHECK(s.longestValidParentheses("(()") == 2);
    CHECK(s.longestValidParentheses(")()())") == 4);
    CHECK(s.longestValidParentheses(")(((((()())()()))()(()))(") == 22);
}

} // namespace longest_valid_parentheses
