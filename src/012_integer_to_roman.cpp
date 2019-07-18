/*
Integer to Roman

URL: https://leetcode.com/problems/integer-to-roman
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

Given an integer, convert it to a roman numeral. Input is guaranteed to be
within the range from 1 to 3999.

Example 1:

    Input:  3
    Output:  "III"

Example 2:

    Input:  4
    Output:  "IV"

Example 3:

    Input:  9
    Output:  "IX"

Example 4:

    Input:  58
    Output:  "LVIII"
    Explanation: L = 50, V = 5, III = 3.


Example 5:

    Input:  1994
    Output:  "MCMXCIV"
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <string>
#include <vector>
#include "catch.hpp"

using std::string;
using std::vector;

namespace integer_to_roman {

namespace v1 {
class Solution {
public:
    string intToRoman(int num) {
        static const vector<char> arrC = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
        static const vector<int> arrI = {1000, 500, 100, 50, 10, 5, 1};

        string result;
        int last = 0;
        for (int i = 0; i < arrI.size() && num > 0; i++) {
            int v = arrI[i];
            int n = num / v;
            num -= n * v;
            if (n != 4) {
                for (int j = 0; j < n; j++) {
                    result += arrC[i];
                }
            } else {
                if (last == 1) {
                    switch (arrC[i]) {
                    case 'I':
                        result[result.size() - 1] = 'I';
                        result += "X";
                        break;
                    case 'X':
                        result[result.size() - 1] = 'X';
                        result += "C";
                        break;
                    case 'C':
                        result[result.size() - 1] = 'C';
                        result += "M";
                        break;
                    }
                } else {
                    switch (arrC[i]) {
                    case 'I':
                        result += "IV";
                        break;
                    case 'X':
                        result += "XL";
                        break;
                    case 'C':
                        result += "CD";
                        break;
                    }
                }
            }
            last = n;
        }

        return result;
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    string intToRoman(int num) {
        static const vector<string> arrC = {"M",  "CM", "D",  "CD", "C",
                                            "XC", "L",  "XL", "X",  "IX",
                                            "V",  "IV", "I"};
        static const vector<int> arrI = {1000, 900, 500, 400, 100, 90, 50,
                                         40,   10,  9,   5,   4,   1};

        string result;
        for (int i = 0; i < arrI.size() && num > 0; i++) {
            int v = arrI[i];
            int n = num / v;
            num -= n * v;
            for (int j = 0; j < n; j++) {
                result += arrC[i];
            }
        }

        return result;
    }
};
} // namespace v2

TEST_CASE("Integer to Roman") {
    Solution s;
    CHECK(s.intToRoman(3) == "III");
    CHECK(s.intToRoman(4) == "IV");
    CHECK(s.intToRoman(9) == "IX");
    CHECK(s.intToRoman(58) == "LVIII");
    CHECK(s.intToRoman(1994) == "MCMXCIV");
}

} // namespace integer_to_roman
