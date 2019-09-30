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

#include <set>
#include "test.h"

using std::set;
using std::string;

namespace longest_substring_without_repeating_characters {

namespace v1 {
/*
首先需要拆解出一个子问题:
**以第 `i` 开始的最长不重复字符串是什么?**

这之后就是以 `i` 迭代求出最大值的问题了.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max = 0;
        for (int i = 0; i < s.length(); i++) {
            set<char> record = {s[i]};
            int j = i + 1;
            for (; j < s.length(); j++) {
                if (record.find(s[j]) != record.end()) {
                    break;
                }
                record.insert(s[j]);
            }
            int len = j - i;
            if (len > max) {
                max = len;
            }
        }
        return max;
    }
};
} // namespace v1

inline namespace v2 {
/*
在 v1 版本的思路上继续优化, 有两个优化的点:

1. 重复计算问题: 例如 "abccd...", 算到 "abcc" 时, 下一步应该直接计算 "cd..."
2. 只要有一个 `j` 走到了结尾, 计算就可以结束, 无需继续迭代 `i`
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max = 0;
        int i = 0, j = 0;
        set<char> record;
        while (j < s.length()) {
            if (record.find(s[j]) == record.end()) {
                record.insert(s[j]);
                auto l = j - i + 1;
                if (l > max) {
                    max = l;
                }
                j++;
            } else {
                // 一旦遇到重复的, 就把 i 往后移动,
                // 直到 i 移动到 j 位置, 就像滑动窗口一样
                record.erase(s[i]);
                i++;
            }
        }
        return max;
    }
};
} // namespace v2

TEST_CASE("Longest Substring Without Repeating Characters") {
    TEST_SOLUTION(lengthOfLongestSubstring, v1, v2) {
        CHECK(lengthOfLongestSubstring("abcabcbb") == 3);
        CHECK(lengthOfLongestSubstring("bbbbb") == 1);
        CHECK(lengthOfLongestSubstring("pwwkew") == 3);

        BENCHMARK("") { return lengthOfLongestSubstring("abcabcbb"); };
    };
}

} // namespace longest_substring_without_repeating_characters
