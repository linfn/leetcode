/*
Maximum Subarray

URL: https://leetcode.com/problems/maximum-subarray
Tags: ['array', 'divide-and-conquer', 'dynamic-programming']
___

Given an integer array `nums`, find the contiguous subarray (containing at
least one number) which has the largest sum and return its sum.

Example:

    Input: [-2,1,-3,4,-1,2,1,-5,4],
    Output: 6
    Explanation:  [4,-1,2,1] has the largest sum = 6.


Follow up:

If you have figured out the O( n ) solution, try coding another solution using
the divide and conquer approach, which is more subtle.
*/

#include <vector>
#include <cassert>
#include "catch.hpp"

using std::vector;

namespace maximum_subarray {

inline namespace v1 {
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        assert(!nums.empty());
        auto prev = nums[0];
        auto max = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (prev > 0) {
                prev = prev + nums[i];
            } else {
                prev = nums[i];
            }
            if (prev > max) {
                max = prev;
            }
        }
        return max;
    }
};
} // namespace v1

TEST_CASE("Maximum Subarray") {
    Solution s;
    auto v = vector<int>{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    CHECK(s.maxSubArray(v) == 6);
}

} // namespace maximum_subarray
