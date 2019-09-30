
/*
Count and Say

URL: https://leetcode.com/problems/count-and-say
Tags: ['string']
___

The count-and-say sequence is the sequence of integers with the first five
terms as following:

    1.     1
    2.     11
    3.     21
    4.     1211
    5.     111221


`1` is read off as `"one 1"` or `11`.
`11` is read off as `"two 1s"` or `21`.
`21` is read off as `"one 2`, then `one 1"` or `1211`.

Given an integer n  where 1 ≤ n ≤ 30, generate the n th term of the count-and-
say sequence.

Note: Each term of the sequence of integers will be represented as a string.



Example 1:

    Input: 1
    Output:  "1"


Example 2:

    Input: 4
    Output:  "1211"
*/

#include <sstream>

#include "test.h"

using std::string;
using std::stringstream;

namespace count_and_say {

inline namespace v1 {
/*
这题主要是要理解题目的意思, 理解了就比较容易了.
核心就是, 前一个数字中每一连续重复的部分都变成 "重复个数"+"数字".
*/
class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        stringstream ss;
        auto prev = countAndSay(n - 1);
        for (int i = 0; i < prev.length();) {
            auto c = prev[i];
            int n = 0;
            do {
                n++;
                i++;
            } while (i < prev.length() && prev[i] == prev[i - 1]);
            ss << n << c;
        }
        return ss.str();
    }
};
} // namespace v1

TEST_CASE("Count and Say") {
    TEST_SOLUTION(countAndSay, v1) {
        CHECK(countAndSay(1) == "1");
        CHECK(countAndSay(4) == "1211");
        CHECK(countAndSay(5) == "111221");
        CHECK(countAndSay(6) == "312211");

        BENCHMARK("") { return countAndSay(10); };
    };
}

} // namespace count_and_say
