
/*
Letter Combinations of a Phone Number

URL: https://leetcode.com/problems/letter-combinations-of-a-phone-number
Tags: ['string', 'backtracking']
___

Given a string containing digits from `2-9` inclusive, return all possible
letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given
below. Note that 1 does not map to any letters.

![](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-
keypad2.svg/200px-Telephone-keypad2.svg.png)

Example:

    Input: "23"
    Output: [ "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].


Note:

Although the above answer is in lexicographical order, your answer could be in
any order you want.
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm> // for test

#include "test.h"

using std::map;
using std::sort; // for test
using std::string;
using std::vector;

namespace letter_combinations_of_a_phone_number {

inline namespace v1 {
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        static map<char, string> digitsMap = {
            {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
        };
        vector<string> result;
        if (digits.empty()) {
            return result;
        }
        result.push_back("");
        for (int i = 0; i < digits.length(); i++) {
            auto letters = digitsMap[digits[i]];
            vector<string> new_result;
            new_result.reserve(result.size() * letters.length());
            for (int j = 0; j < letters.length(); j++) {
                for (auto s : result) {
                    new_result.push_back(s + letters[j]);
                }
            }
            result = new_result;
        }
        return result;
    }
};
} // namespace v1

namespace v2 {
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        backtrack("", digits, result);
        return result;
    }

private:
    void backtrack(const string& s, const string& digits,
                   vector<string>& result) {
        static map<char, string> digitsMap = {
            {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
        };
        if (digits.empty()) {
            result.push_back(s);
            return;
        }
        for (auto l : digitsMap[digits[0]]) {
            backtrack(s + l, digits.substr(1), result);
        }
    }
};
} // namespace v2

TEST_CASE("Letter Combinations of a Phone Number") {
    TEST_SOLUTION(letterCombinations, v1, v2) {
        auto v1 = letterCombinations("23");
        auto v2 = vector<string>{"ad", "ae", "af", "bd", "be",
                                 "bf", "cd", "ce", "cf"};
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        CHECK(v1 == v2);

        BENCHMARK("") { return letterCombinations("234"); };
    };
}

} // namespace letter_combinations_of_a_phone_number
