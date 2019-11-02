
/*
Minimum Window Substring

URL: https://leetcode.com/problems/minimum-window-substring
Tags: ['hash-table', 'two-pointers', 'string', 'sliding-window']
___

Given a string S and a string T, find the minimum window in S which will
contain all the characters in T in complexity O(n).

Example:

    Input: S =  "ADOBECODEBANC", T =  "ABC"
    Output:  "BANC"


Note:

  * If there is no such window in S that covers all characters in T, return the
empty string `""`.
  * If there is such window, you are guaranteed that there will always be only
one unique minimum window in S.
*/

#include <unordered_set>
#include "test.h"

using std::string;

namespace minimum_window_substring {

/*
    Sliding Window
    1. 初始 start, end 两个指针指向 s[0];
    2. 移动 end 指针, 直到 window 为一个有效的结果
    3. 移动 start 指针, 直到 window 为一个非有效结果
    4. 重复 2 和 3
*/
inline namespace v1 {
using std::unordered_map;
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> counter;
        for (auto c : t) {
            counter[c]++;
        }
        int totalRemain = counter.size();
        int minStart = -1, minLen = 0;
        int start = 0;
        for (int i = 0; i < s.length(); i++) {
            auto it = counter.find(s[i]);
            if (it != counter.end()) {
                it->second--;
                if (it->second == 0) {
                    totalRemain--;
                    if (totalRemain == 0) { // 有效结果
                        for (; start <= i; start++) {
                            auto it2 = counter.find(s[start]);
                            if (it2 != counter.end()) {
                                it2->second++;
                                if (it2->second > 0) { // 下一个即为非有效结果
                                    int len = i - start + 1;
                                    if (minStart == -1 || len < minLen) {
                                        minStart = start;
                                        minLen = len;
                                    }
                                    start++;
                                    totalRemain = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (minStart == -1) {
            return "";
        }
        return s.substr(minStart, minLen);
    }
};
} // namespace v1

TEST_CASE("Minimum Window Substring") {
    TEST_SOLUTION(minWindow, v1) {
        CHECK(minWindow("ADOBECODEBANC", "ABC") == "BANC");
        CHECK(minWindow("a", "aa") == "");
        CHECK(minWindow("acbbaca", "aba") == "baca");
        CHECK(minWindow("a", "a") == "a");
    };
}

} // namespace minimum_window_substring
