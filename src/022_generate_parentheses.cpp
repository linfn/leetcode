
/*
Generate Parentheses

URL: https://leetcode.com/problems/generate-parentheses
Tags: ['string', 'backtracking']
___

Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.

For example, given n = 3, a solution set is:

    [
      "((()))",
      "(()())",
      "(())()",
      "()(())",
      "()()()"
    ]
*/

#include <vector>
#include <string>
#include <iostream>

#include "test.h"

using std::string;
using std::vector;

namespace generate_parentheses {

inline namespace v1 {
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if (n == 0) {
            return result;
        }
        backtracking("", n, n, result);
        return result;
    }

private:
    void backtracking(const string& state, int l, int r,
                      vector<string>& result) {
        if (l == 0 && r == 0) {
            result.push_back(state);
            return;
        }
        if (l == r) {
            backtracking(state + '(', l - 1, r, result);
        } else {
            if (l > 0) {
                backtracking(state + '(', l - 1, r, result);
            }
            if (r > 0) {
                backtracking(state + ')', l, r - 1, result);
            }
        }
    }
};
} // namespace v1

TEST_CASE("Generate Parentheses") {
    TEST_SOLUTION(generateParenthesis, v1) {
        CHECK(generateParenthesis(3) ==
              vector<string>{"((()))", "(()())", "(())()", "()(())", "()()()"});
        BENCHMARK(""){};
    };
}

} // namespace generate_parentheses
