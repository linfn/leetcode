/*
Regular Expression Matching

URL: https://leetcode.com/problems/regular-expression-matching
Tags: ['string', 'dynamic-programming', 'backtracking']
___

Given an input string (`s`) and a pattern (`p`), implement regular expression
matching with support for `'.'` and `'*'`.



    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.


The matching should cover the entire input string (not partial).

Note:

  * `s` could be empty and contains only lowercase letters `a-z`.
  * `p` could be empty and contains only lowercase letters `a-z`, and characters
like `.` or `*`.

Example 1:

    Input:
    s =  "aa"
    p = "a"
    Output: false
    Explanation:  "a" does not match the entire string "aa".


Example 2:

    Input:
    s =  "aa"
    p = "a*"
    Output: true
    Explanation:  '*' means zero or more of the preceding element, 'a'.
Therefore, by repeating 'a' once, it becomes "aa".


Example 3:

    Input:
    s =  "ab"
    p = ".*"
    Output: true
    Explanation:  ".*" means "zero or more (*) of any character (.)".


Example 4:

    Input:
    s =  "aab"
    p = "c*a*b"
    Output: true
    Explanation:  c can be repeated 0 times, a can be repeated 1 time.
Therefore, it matches "aab".


Example 5:

    Input:
    s =  "mississippi"
    p = "mis*is*p*."
    Output: false
*/

#include <string>
#include <memory>
#include "test.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

namespace regular_expression_matching {

inline namespace v1 {
class Solution {
public:
    bool isMatch(string s, string p) {
        shared_ptr<State> machine = nullptr;
        shared_ptr<State> cur = nullptr;
        for (auto i = 0; i < p.length(); i++) {
            if (p[i] == '*') {
                if (cur) {
                    cur->repeated_ = true;
                }
                continue;
            }
            auto state = make_shared<State>(p[i]);
            if (cur) {
                cur->next_ = state;
            } else {
                machine = state;
            }
            cur = state;
        }

        if (machine) {
            return machine->input(s, 0);
        }
        return s.empty();
    }

private:
    class State {
        char c_;

    public:
        bool repeated_ = false;
        shared_ptr<State> next_ = nullptr;

        State(char c) : c_(c) {}
        bool input(const string& s, int pos) {
            // 对于每一个带 "*" 的状态, 需要尝试两个方向:
            // 1. 不读取输入的情况下跳转到下一个状态
            // 2. 读取一个输入进行匹配判断, 再跳转回自己
            // 两个中有任意一个成功匹配, 则成功匹配.
            if (repeated_ && next_) {
                if (next_->input(s, pos)) {
                    return true;
                }
            }
            if (pos >= s.length()) {
                if (repeated_ && !next_) {
                    return true;
                }
                return false;
            }
            if (c_ == s[pos] || c_ == '.') {
                if (repeated_) {
                    return this->input(s, pos + 1);
                } else {
                    if (next_) {
                        return next_->input(s, pos + 1);
                    } else {
                        return pos == s.length() - 1;
                    }
                }
            } else {
                return false;
            }
        }
    };
};
} // namespace v1

TEST_CASE("Regular Expression Matching") {
    TEST_SOLUTION(isMatch, v1) {
        CHECK_FALSE(isMatch("aa", "a"));
        CHECK(isMatch("aa", "a*"));
        CHECK(isMatch("ab", ".*"));
        CHECK(isMatch("aab", "c*a*b*"));
        CHECK_FALSE(isMatch("mississippi", "mis*is*p*."));
        CHECK(isMatch("aaa", "a*a"));
        CHECK(isMatch("aaa", "ab*a*c*a"));
        CHECK_FALSE(isMatch("ab", ".*c"));
        CHECK(isMatch("a", "ab*"));

        BENCHMARK("") { return isMatch("aaa", "ab*a*c*a"); };
    };
}

} // namespace regular_expression_matching
