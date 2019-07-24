/*
3Sum Closest

URL: https://leetcode.com/problems/3sum-closest
Tags: ['array', 'two-pointers']
___

Given an array `nums` of n integers and an integer `target`, find three
integers in `nums` such that the sum is closest to `target`. Return the sum of
the three integers. You may assume that each input would have exactly one
solution.

Example:

    Given array nums = [-1, 2, 1, -4], and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <vector>
#include <algorithm>
#include <cmath>
#include "test.h"

using std::vector;

namespace three_sum_closest {

inline namespace v1 {
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        // 这里可以稍微改一下,
        // 由于最初没有可以比较的值, 所以这里用了int max来替代,
        // 更好是直接使用 target - nums[0] - nums[1] - nums[2]来替代
        int diff = std::numeric_limits<int>::max();
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            int a = target - nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int b = a - nums[left] - nums[right];
                if (b == 0) {
                    return target;
                } else {
                    if (b > 0) {
                        left++;
                    } else {
                        right--;
                    }
                }
                if (std::abs(diff) > std::abs(b)) {
                    diff = b;
                }
            }
        }
        return target - diff;
    }
};
} // namespace v1

TEST_CASE("3Sum Closest") {
    TEST_SOLUTION(threeSumClosest, v1) {
        vector<int> v{-1, 2, 1, -4};
        CHECK(threeSumClosest(v, 1) == 2);
        v = {1, 2, 5, 10, 11};
        CHECK(threeSumClosest(v, 12) == 13);

        BENCHMARK("") { return threeSumClosest(v, 12); };
    };
}

} // namespace three_sum_closest
