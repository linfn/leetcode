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
#include "test.h"

using std::string;

namespace longest_palindromic_substring {

namespace v1 {
/*
分解子问题: **以第 `i` 开始的最长回文是什么?**
然后再迭代求最大值.

但从开始处来判断回文不是很便利, 所以 v2 中改为从中心处来计算.
*/
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
分解子问题: **以第 `i` 或 `(i, i+1)`` 为中心的最长回文是什么?**
然后再迭代求最大值.
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
    TEST_SOLUTION(longestPalindrome, v1, v2) {
        CHECK(longestPalindrome("") == "");
        CHECK(longestPalindrome("babad") == "bab");
        CHECK(longestPalindrome("cbbd") == "bb");

        BENCHMARK("") { return longestPalindrome("cbbd"); };
    };
}

} // namespace longest_palindromic_substring
