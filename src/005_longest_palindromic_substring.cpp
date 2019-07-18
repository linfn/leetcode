/*
Longest Palindromic Substring

URL: https://leetcode.com/problems/longest-palindromic-substring
Tags: ['string', 'dynamic-programming']
___

Given a string s , find the longest palindromic substring in s. You may assume
that the maximum length of s is 1000.

Example 1:

    Input:  "babad"
    Output:  "bab"
    Note:  "aba" is also a valid answer.


Example 2:

    Input:  "cbbd"
    Output:  "bb"
*/

#include <string>
#include <tuple>
#include "catch.hpp"

using std::string;

namespace longest_palindromic_substring {

namespace v1 {
class Solution {
public:
    string longestPalindrome(string s) {
        string result = "";
        int max = 0;
        for (auto i = 0; i < s.length(); i++) {
            for (auto j = s.length() - 1; i <= j; j--) {
                if (isPalindrome(s, i, j)) {
                    auto l = j - i + 1;
                    if (l > max) {
                        max = l;
                        result = s.substr(i, l);
                    }
                    break;
                }
            }
        }
        return result;
    }

private:
    bool isPalindrome(const string& s, int i, int j) const {
        if (i >= j) {
            return true;
        }
        if (s[i] != s[j]) {
            return false;
        }
        return isPalindrome(s, i + 1, j - 1);
    }
};
} // namespace v1

inline namespace v2 {
/*
回文公理:
1. 空 是回文
2. x 是回文
3. x回文x 是回文
所以迭代思路就是:
分别遍历所有“空”形式的(间隔), “x”形式的(单字母) 的初始项,
再在初始项的基础上借助规则 3, 向外扩展, 找出最长的项.
*/
class Solution {
public:
    string longestPalindrome(string s) {
        int pos = 0, length = 0;
        for (auto i = 0; i < s.length(); i++) {
            auto r = longest(s, i, i);
            if (std::get<1>(r) > length) {
                pos = std::get<0>(r);
                length = std::get<1>(r);
            }
            r = longest(s, i, i + 1);
            if (std::get<1>(r) > length) {
                pos = std::get<0>(r);
                length = std::get<1>(r);
            }
        }
        return s.substr(pos, length);
    }

private:
    std::tuple<int, int> longest(const string& s, int i, int j) const {
        auto r = std::make_tuple(0, 0);
        for (; i >= 0 && j < s.length(); i--, j++) {
            if (s[i] == s[j]) {
                r = std::make_tuple(i, j - i + 1);
            } else {
                break;
            }
        }
        return r;
    }
};
} // namespace v2

TEST_CASE("Longest Palindromic Substring") {
    Solution s;
    REQUIRE(s.longestPalindrome("") == "");
    REQUIRE(s.longestPalindrome("babad") == "bab");
    REQUIRE(s.longestPalindrome("cbbd") == "bb");
}

} // namespace longest_palindromic_substring
