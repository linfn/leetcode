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

#include "test.h"

using std::string;
using std::vector;

namespace longest_valid_parentheses {

/*
比较 v1 和 v2 版本,
首先他们都拆出了一个子问题: 以第 `i` 开始/结束的最长匹配是多少?
然后都是迭代求最值.

v2 动态规划思路的区别于 v1 就在于对子问题的解决上.
动态规划使用递归定义的方式定义了子问题的解,
使每一步的计算都转换为了在之前计算结果基础之上的增量计算.
通过缓存每一步的计算结果就可以避免重复计算.
*/

namespace v1 {
class Solution {
public:
    int longestValidParentheses(string s) {
        int max = 0;
        for (int i = 0; i < s.length(); i++) {
            auto len = longest(s, i);
            if (len > max) {
                max = len;
            }
        }
        return max;
    }

private:
    int longest(string s, int i) {
        int len = 0, sum = 0, cur = 0;
        for (; i < s.length(); i++) {
            int c = s[i] == '(' ? 1 : -1;
            if (sum + c < 0) {
                break;
            }
            sum += c;
            cur++;
            if (sum == 0) {
                len = cur;
            }
        }
        return len;
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
        vector<int> record(s.size(), 0);
        const auto dp = [&record](int i) { return i < 0 ? 0 : record[i]; };
        const auto str = [&s](int i) { return i < 0 ? '_' : s[i]; };
        int max = 0;
        for (int i = 1; i < s.length(); i++) {
            if (str(i) == ')') {
                if (str(i - 1) == '(') {
                    record[i] = dp(i - 2) + 2;
                } else {
                    if (str(i - dp(i - 1) - 1) == '(') {
                        record[i] = dp(i - 1) + dp(i - dp(i - 1) - 2) + 2;
                    }
                }
            }
            if (dp(i) > max) {
                max = dp(i);
            }
        }
        return max;
    }
};
} // namespace v2

TEST_CASE("Longest Valid Parentheses") {
    TEST_SOLUTION(longestValidParentheses, v1, v2) {
        CHECK(longestValidParentheses("(()") == 2);
        CHECK(longestValidParentheses(")()())") == 4);
        CHECK(longestValidParentheses(")(((((()())()()))()(()))(") == 22);

        BENCHMARK("") {
            return longestValidParentheses(")(((((()())()()))()(()))(");
        };
    };
}

} // namespace longest_valid_parentheses
