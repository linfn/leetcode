/*
String to Integer (atoi)

URL: https://leetcode.com/problems/string-to-integer-atoi
Tags: ['math', 'string']
___

Implement `atoi` which converts a string to an integer.

The function first discards as many whitespace characters as necessary until
the first non-whitespace character is found. Then, starting from this
character, takes an optional initial plus or minus sign followed by as many
numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the
integral number, which are ignored and have no effect on the behavior of this
function.

If the first sequence of non-whitespace characters in str is not a valid
integral number, or if no such sequence exists because either str is empty or
it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

  * Only the space character `' '` is considered as whitespace character.
  * Assume we are dealing with an environment which could only store integers
within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If the numerical
value is out of the range of representable values, INT_MAX (2^31 − 1) or INT_MIN
(−2^31) is returned.

Example 1:

    Input:  "42"
    Output: 42


Example 2:

    Input:  "   -42"
    Output: -42
    Explanation: The first non-whitespace character is  '-', which is the minus
sign. Then take as many numerical digits as possible, which gets 42.


Example 3:

    Input:  "4193 with words"
    Output: 4193
    Explanation: Conversion stops at digit  '3' as the next character is not a
numerical digit.


Example 4:

    Input:  "words and 987"
    Output: 0
    Explanation: The first non-whitespace character is  'w', which is not a
numerical digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:

    Input:  "-91283472332"
    Output: -2147483648
    Explanation: The number  "-91283472332" is out of the range of a 32-bit
signed integer. Thefore INT_MIN (−2^31) is returned.
*/

#include <string>
#include <map>
#include <numeric>
#include "test.h"

using std::map;
using std::string;

namespace string_to_integer_atoi {

inline namespace v1 {
class Solution {
public:
    int myAtoi(string str) {
        static const map<char, int> numMap = {
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
            {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        };
        static const auto minHead = std::numeric_limits<int>::min() / 10;
        static const auto minTail = std::numeric_limits<int>::min() % 10;
        static const auto maxHead = std::numeric_limits<int>::max() / 10;
        static const auto maxTail = std::numeric_limits<int>::max() % 10;

        auto i = str.find_first_not_of(' ');
        if (i == string::npos) {
            return 0;
        }
        int sign = 0;
        auto c = str[i];
        if (c == '+') {
            sign++;
            i++;
        } else if (c == '-') {
            sign--;
            i++;
        }

        int result = 0;
        for (; i < str.length(); i++) {
            auto it = numMap.find(str[i]);
            if (it == numMap.end()) {
                break;
            }
            auto delta = (sign >= 0 ? it->second : -it->second);
            if (result <= minHead) {
                if (result == minHead) {
                    if (delta < minTail) {
                        return std::numeric_limits<int>::min();
                    }
                } else {
                    return std::numeric_limits<int>::min();
                }
            } else if (result >= maxHead) {
                if (result == maxHead) {
                    if (delta > maxTail) {
                        return std::numeric_limits<int>::max();
                    }
                } else {
                    return std::numeric_limits<int>::max();
                }
            }
            result = result * 10 + delta;
        }
        return result;
    }
};

} // namespace v1

TEST_CASE("String to Integer (atoi)") {
    TEST_SOLUTION(myAtoi, v1) {
        CHECK(myAtoi("42") == 42);
        CHECK(myAtoi("   -42") == -42);
        CHECK(myAtoi("4193 with words") == 4193);
        CHECK(myAtoi("words and 987") == 0);
        CHECK(myAtoi("-91283472332") == -2147483648);
        CHECK(myAtoi("+-1") == 0);

        BENCHMARK("") { return myAtoi("-91283472332"); };
    };
}

} // namespace string_to_integer_atoi
