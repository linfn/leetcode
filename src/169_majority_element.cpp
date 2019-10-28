
/*
Majority Element

URL: https://leetcode.com/problems/majority-element
Tags: ['array', 'divide-and-conquer', 'bit-manipulation']
___

Given an array of size n , find the majority element. The majority element is
the element that appears more than `⌊ n/2 ⌋` times.

You may assume that the array is non-empty and the majority element always
exist in the array.

Example 1:

    Input: [3,2,3]
    Output: 3

Example 2:

    Input: [2,2,1,1,1,2,2]
    Output: 2
*/

#include "test.h"

using std::vector;

namespace majority_element {

namespace v1 {
using std::unordered_map;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int target = nums.size() / 2;
        unordered_map<int, int> counters;
        for (auto n : nums) {
            if ((++counters[n]) > target) {
                return n;
            }
        }
        return 0;
    }
};
} // namespace v1

/*
    Boyer-Moore Voting Algorithm
*/
inline namespace v2 {
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0, result;
        for (auto n : nums) {
            if (count == 0) {
                result = n;
            }
            count += (n == result ? 1 : -1);
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Majority Element") {
    TEST_SOLUTION(majorityElement, v1, v2) {
        vector<int> v = {3, 2, 3};
        CHECK(majorityElement(v) == 3);
        v = {2, 2, 1, 1, 1, 2, 2};
        CHECK(majorityElement(v) == 2);

        v = {2, 2, 1, 1, 1, 2, 2};
        BENCHMARK("") { return majorityElement(v); };
    };
}

} // namespace majority_element
