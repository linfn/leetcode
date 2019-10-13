
/*
Single Number

URL: https://leetcode.com/problems/single-number
Tags: ['hash-table', 'bit-manipulation']
___

Given a non-empty  array of integers, every element appears twice except for
one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it
without using extra memory?

Example 1:

    Input: [2,2,1]
    Output: 1


Example 2:

    Input: [4,1,2,1,2]
    Output: 4
*/

#include <unordered_set>
#include "test.h"

using std::vector;

namespace single_number {

namespace v1 {
using std::unordered_set;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> set;
        for (auto n : nums) {
            auto i = set.find(n);
            if (i == set.end()) {
                set.insert(n);
            } else {
                set.erase(i);
            }
        }
        return *set.begin();
    }
};
} // namespace v1

/*
    使用 XOR 运算的特性, 剔除重复值
*/
inline namespace v2 {
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (auto n : nums) {
            result ^= n;
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Single Number") {
    TEST_SOLUTION(singleNumber, v1, v2) {
        vector<int> v = {2, 2, 1};
        CHECK(singleNumber(v) == 1);

        v = {2, 2, 1, 3, 4, 5, 5, 4, 3};
        BENCHMARK("") { return singleNumber(v); };
    };
}

} // namespace single_number
