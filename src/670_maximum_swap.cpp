
/*
Maximum Swap

URL: https://leetcode.com/problems/maximum-swap
Tags: ['array', 'math']
___

Given a non-negative integer, you could swap two digits at most once to get
the maximum valued number. Return the maximum valued number you could get.

Example 1:

    Input: 2736
    Output: 7236
    Explanation: Swap the number 2 and the number 7.


Example 2:

    Input: 9973
    Output: 9973
    Explanation: No swap.


Note:

  1. The given number is in the range [0, 108]
*/

#include <vector>

#include "test.h"

using namespace std;

namespace maximum_swap {

inline namespace v1 {
class Solution {
public:
    int maximumSwap(int num) {
        vector<int> v;
        do {
            v.push_back(num % 10);
            num = num / 10;
        } while (num > 0);
        for (int i = v.size() - 1; i >= 1; i--) {
            int maxj = i;
            for (int j = 0; j < i; j++) {
                if (v[j] > v[maxj]) {
                    maxj = j;
                }
            }
            if (maxj != i) {
                swap(v[i], v[maxj]);
                break;
            }
        }
        int result = 0;
        for (int i = v.size() - 1; i >= 0; i--) {
            result = result * 10 + v[i];
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Maximum Swap") {
    TEST_SOLUTION(maximumSwap, v1) {
        CHECK(maximumSwap(2736) == 7236);
        CHECK(maximumSwap(9973) == 9973);
        CHECK(maximumSwap(1993) == 9913);

        BENCHMARK("") { return maximumSwap(1993); };
    };
}

} // namespace maximum_swap
