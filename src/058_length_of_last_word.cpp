
/*
Length of Last Word

URL: https://leetcode.com/problems/length-of-last-word
Tags: ['string']
___

Given a string s consists of upper/lower-case alphabets and empty space
characters `' '`, return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space
characters only.

Example:

    Input:  "Hello World"
    Output: 5
*/

#include "test.h"

using std::string;

namespace length_of_last_word {

inline namespace v1 {
/*
    这个思路是从头到尾迭代, 还有中思路是从尾到头
*/
class Solution {
public:
    int lengthOfLastWord(string s) {
        int result = 0, n = 0;
        // 字符串迭代结束本身也是一种输入时可以这样处理
        for (int i = 0; i <= s.length(); i++) {
            if (i == s.length() || s[i] == ' ') {
                if (n != 0) {
                    result = n;
                    n = 0;
                }
            } else {
                n++;
            }
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Length of Last Word") {
    TEST_SOLUTION(lengthOfLastWord, v1) {
        CHECK(lengthOfLastWord("Hello World") == 5);
        CHECK(lengthOfLastWord("a") == 1);
        CHECK(lengthOfLastWord("a   b     ") == 1);
    };
}

} // namespace length_of_last_word
