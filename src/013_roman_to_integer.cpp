/*
Roman to Integer

URL: https://leetcode.com/problems/roman-to-integer
Tags: ['math', 'string']
___

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`,
`C`, `D` and `M`.


    
    Symbol       Value
    I             1
    V             5
    X             10
    L             50
    C             100
    D             500
    M             1000

For example, two is written as `II` in Roman numeral, just two one's added
together. Twelve is written as, `XII`, which is simply `X` \+ `II`. The number
twenty seven is written as `XXVII`, which is `XX` \+ `V` \+ `II`.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not `IIII`. Instead, the number four is
written as `IV`. Because the one is before the five we subtract it making
four. The same principle applies to the number nine, which is written as `IX`.
There are six instances where subtraction is used:

  * `I` can be placed before `V` (5) and `X` (10) to make 4 and 9.
  * `X` can be placed before `L` (50) and `C` (100) to make 40 and 90.
  * `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be
within the range from 1 to 3999.

Example 1:

    Input:  "III"
    Output: 3

Example 2:

    Input:  "IV"
    Output: 4

Example 3:

    Input:  "IX"
    Output: 9

Example 4:

    Input:  "LVIII"
    Output: 58
    Explanation: L = 50, V= 5, III = 3.


Example 5:

    Input:  "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <string>
#include <vector>
#include "catch.hpp"

using std::string;
using std::vector;

namespace roman_to_integer {

inline namespace v1 {
class Solution {
public:
    int romanToInt(string s) {
        static const vector<string> arrC = {"M",  "CM", "D",  "CD", "C",
                                            "XC", "L",  "XL", "X",  "IX",
                                            "V",  "IV", "I"};
        static const vector<int> arrI = {1000, 900, 500, 400, 100, 90, 50,
                                         40,   10,  9,   5,   4,   1};

        int result = 0;
        string::size_type head = 0;
        for (int i = 0; i < arrC.size() && head < s.size();) {
            if (s.compare(head, arrC[i].size(), arrC[i]) == 0) {
                result += arrI[i];
                head += arrC[i].size();
            } else {
                i++;
            }
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Roman to Integer") {
    Solution s;
    CHECK(s.romanToInt("III") == 3);
    CHECK(s.romanToInt("IV") == 4);
    CHECK(s.romanToInt("IX") == 9);
    CHECK(s.romanToInt("LVIII") == 58);
    CHECK(s.romanToInt("MCMXCIV") == 1994);
}

} // namespace roman_to_integer
