
/*
Implement strStr()

URL: https://leetcode.com/problems/implement-strstr
Tags: ['two-pointers', 'string']
___

Implement [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or -1 if
needle is not part of haystack.

Example 1:

    Input: haystack =  "hello", needle = "ll"
    Output: 2


Example 2:

    Input: haystack =  "aaaaa", needle = "bba"
    Output: -1


Clarification:

What should we return when `needle` is an empty string? This is a great
question to ask during an interview.

For the purpose of this problem, we will return 0 when `needle` is an empty
string. This is consistent to C's
[strstr()](http://www.cplusplus.com/reference/cstring/strstr/) and Java's
[indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf\(java.lang.String\)).
*/

#include "test.h"

using std::string;

namespace implement_strstr {

inline namespace v1 {
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        int size = haystack.length() - needle.length() + 1;
        for (int i = 0; i < size; i++) {
            if (check(haystack, i, needle)) {
                return i;
            }
        }
        return -1;
    }

private:
    bool check(const string& haystack, int i, const string& needle) {
        for (int j = 0; j < needle.length(); j++) {
            if (needle[j] != haystack[i + j]) {
                return false;
            }
        }
        return true;
    }
};
} // namespace v1

TEST_CASE("Implement strStr()") {
    TEST_SOLUTION(strStr, v1) {
        CHECK(strStr("hello", "ll") == 2);
        CHECK(strStr("aaaaa", "bba") == -1);
        CHECK(strStr("a", "") == 0);
        CHECK(strStr("a", "a") == 0);
        CHECK(strStr("mississippi", "issip") == 4);
        CHECK(strStr("abbbbbaabbaabaabbbaaaaabbabbbabbbbbaababaabbaabbbbbababaa"
                     "babbbbaaabbbbabaabaaaabbbbabbbaabbbaabbaaabaabaaaaaaaa",
                     "abbbaababbbabbbabbbbbabaaaaaaabaabaabbbbaabab") == -1);

        BENCHMARK("") {
            return strStr(
                "abbbbbaabbaabaabbbaaaaabbabbbabbbbbaababaabbaabbbbbababaa"
                "babbbbaaabbbbabaabaaaabbbbabbbaabbbaabbaaabaabaaaaaaaa",
                "abbbaababbbabbbabbbbbabaaaaaaabaabaabbbbaabab");
        };
    };
}

} // namespace implement_strstr
