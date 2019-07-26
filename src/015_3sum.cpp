/*
3Sum

URL: https://leetcode.com/problems/3sum
Tags: ['array', 'two-pointers']
___

Given an array `nums` of n integers, are there elements a , b , c in `nums`
such that a \+ b \+ c = 0? Find all unique triplets in the array which gives
the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

    Given array nums = [-1, 0, 1, 2, -1, -4],

    A solution set is:
    [
      [-1, 0, 1],
      [-1, -1, 2]
    ]
*/

#include <vector>
#include <algorithm>
#include "test.h"

using std::lower_bound;
using std::sort;
using std::vector;

namespace three_sum {

/*
我一开始的想法是固定住一个数, 然后就转变成一个 two-sum 问题.
但这样太慢了.

这里重要的一点是先需要对输入做排序, 在有序的基础上能够更高效的查找目标
(两端往中间逼近).
*/

namespace v1 {
// Time Limit Exceeded
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        for (int i = 0; i < nums.size() - 2; i++) {
            for (int j = i + 1; j < nums.size() - 1; j++) {
                for (int k = j + 1; k < nums.size(); k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> v{nums[i], nums[j], nums[k]};
                        sort(v.begin(), v.end());
                        auto it = lower_bound(result.begin(), result.end(), v);
                        if (it == result.end() || *it != v) {
                            result.insert(it, move(v));
                        }
                    }
                }
            }
        }
        return result;
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 排序后, 固定三元组最左侧的一个数字, 然后让右侧的数组两端往中间逼近.
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0) {
                if (nums[i] == nums[i - 1]) {
                    continue; // 去重
                }
            }
            int target = -nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                auto sum = nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                }
                bool moveRight = false;
                if (sum >= target) {
                    moveRight = true;
                }
                if (moveRight) {
                    do {
                        right--;
                        // 这一部分 while 是为了去除重复值
                    } while (left < right && nums[right] == nums[right + 1]);
                } else {
                    do {
                        left++;
                    } while (left < right && nums[left] == nums[left - 1]);
                }
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("3Sum") {
    TEST_SOLUTION(threeSum, v1, v2) {
        vector<int> v = {-1, 0, 1, 2, -1, -4};
        CHECK(threeSum(v) == vector<vector<int>>({{-1, -1, 2}, {-1, 0, 1}}));
        BENCHMARK("") { return threeSum(v); };
    };
}

} // namespace three_sum
