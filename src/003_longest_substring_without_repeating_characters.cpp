/*
Longest Substring Without Repeating Characters

URL:
https://leetcode.com/problems/longest-substring-without-repeating-characters
Tags: ['hash-table', 'two-pointers', 'string', 'sliding-window']
___

Given a string, find the length of the longest substring without repeating
characters.

Example 1:

    Input: "abcabcbb"
    Output: 3
    Explanation: The answer is "abc", with the length of 3.


Example 2:

    Input: "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.


Example 3:

    Input: "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3.
                 Note that the answer must be a substring , "pwke" is a
subsequence and not a substring.
*/

#include <string>
#include <set>
#include "catch.hpp"

using std::set;
using std::string;

namespace longest_substring_without_repeating_characters {

namespace v1 {
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max = 0;
        for (auto i = 0; i < s.length(); i++) {
            int length = 0;
            set<char> record;
            auto j = i;
            for (; j < s.length(); j++) {
                if (record.find(s[j]) != record.end()) {
                    length = j - i;
                    break;
                }
                record.insert(s[j]);
            }
            if (j == s.length()) {
                length = j - i;
            }
            if (length > max) {
                max = length;
            }
        }
        return max;
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int i = 0, j = 0;
        set<char> record;
        while (j < s.length()) {
            if (record.find(s[j]) == record.end()) {
                record.insert(s[j]);
                auto l = j - i + 1;
                if (l > result) {
                    result = l;
                }
                j++;
            } else {
                // 一旦遇到重复的, 就从头开始往后剔除, 直到把重复的项剔除为止,
                // 然后继续上面分支里的计数.
                record.erase(s[i]);
                i++;
            }
        }
        return result;
    }
};
} // namespace v2

namespace v3 {
// 动态规划思路, 时间上比不过 v2 版本
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        int n = 1, max = 1;
        for (auto i = 1; i < s.length(); i++) {
            auto c = s[i];
            bool find = false;
            for (auto j = i - 1; j >= i - n; j--) {
                if (s[j] == c) {
                    n = i - j;
                    find = true;
                    break;
                }
            }
            if (!find) {
                n++;
                if (n > max) {
                    max = n;
                }
            }
        }
        return max;
    }
};
} // namespace v3

TEST_CASE("Longest Substring Without Repeating Characters") {
    Solution s;
    REQUIRE(s.lengthOfLongestSubstring("abcabcbb") == 3);
    REQUIRE(s.lengthOfLongestSubstring("bbbbb") == 1);
    REQUIRE(s.lengthOfLongestSubstring("pwwkew") == 3);
}

} // namespace longest_substring_without_repeating_characters
