
/*
Longest Common Prefix

URL: https://leetcode.com/problems/longest-common-prefix
Tags: ['string']
___

Write a function to find the longest common prefix string amongst an array of
strings.

If there is no common prefix, return an empty string `""`.

Example 1:

    Input: ["flower","flow","flight"]
    Output:  "fl"


Example 2:

    Input: ["dog","racecar","car"]
    Output:  ""
    Explanation: There is no common prefix among the input strings.


Note:

All given inputs are in lowercase letters `a-z`.
*/

#include <string>
#include <vector>
#include "test.h"

using std::string;
using std::vector;

namespace longest_common_prefix {

/*
该题的[解决方案页面](https://leetcode.com/articles/longest-common-prefix/)提供了非常丰富的不同思路.
例如: 用 reduce 的方式

1. LCP(s1...sn) = LCP(LCP(LCP(s1), s2)..., sn)
2. LCP(s1...sn) = LCP(LCP(s1...sx), LCP(sx+1...sn))
*/

inline namespace v1 {
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        const auto& s = strs[0];
        int pos = 0;
        for (; pos < s.length(); pos++) {
            for (int i = 1; i < strs.size(); i++) {
                if (strs[i].length() <= pos || strs[i][pos] != s[pos]) {
                    goto RESULT;
                }
            }
        }
    RESULT:
        return s.substr(0, pos);
    }
};
} // namespace v1

TEST_CASE("Longest Common Prefix") {
    TEST_SOLUTION(longestCommonPrefix, v1) {
        vector<string> v = {"flower", "flow", "flight"};
        CHECK(longestCommonPrefix(v) == "fl");
        v = {"dog", "racecar", "car"};
        CHECK(longestCommonPrefix(v) == "");

        BENCHMARK("") { return longestCommonPrefix(v); };
    };
}

} // namespace longest_common_prefix
