
/*
4Sum

URL: https://leetcode.com/problems/4sum
Tags: ['array', 'hash-table', 'two-pointers']
___

Given an array `nums` of n integers and an integer `target`, are there
elements a , b , c , and d in `nums` such that a \+ b \+ c \+ d = `target`?
Find all unique quadruplets in the array which gives the sum of `target`.

Note:

The solution set must not contain duplicate quadruplets.

Example:

    Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

    A solution set is:
    [
      [-1,  0, 0, 1],
      [-2, -1, 1, 2],
      [-2,  0, 0, 2]
    ]
*/

#include "test.h"

using std::sort;
using std::vector;

namespace four_sum {

inline namespace v1 {
/*
沿用 3Sum 的思路
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return nSum(nums, 0, 4, target);
    }

private:
    vector<vector<int>> nSum(const vector<int>& nums, int begin, int n,
                             int target) {
        if (n == 2) {
            return twoSum(nums, begin, int(nums.size()) - 1, target);
        }
        vector<vector<int>> result;
        while (begin + (n - 1) < nums.size()) {
            int t = target - nums[begin];
            auto subResult = nSum(nums, begin + 1, n - 1, t);
            for (auto& v : subResult) {
                v.push_back(nums[begin]);
            }
            result.insert(result.end(), subResult.begin(), subResult.end());
            do {
                begin++;
            } while (begin + (n - 1) < nums.size() &&
                     nums[begin] == nums[begin - 1]);
        }
        return result;
    }
    vector<vector<int>> twoSum(const vector<int>& nums, int left, int right,
                               int target) {
        vector<vector<int>> result;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum >= target) {
                if (sum == target) {
                    result.push_back({nums[left], nums[right]});
                }
                do {
                    right--;
                } while (left < right && nums[right] == nums[right + 1]);
            } else {
                do {
                    left++;
                } while (left < right && nums[left] == nums[left - 1]);
            }
        }
        return result;
    }
};
} // namespace v1

template <typename VV>
bool equalVV(VV lhs, VV rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (auto& v : lhs) {
        std::sort(v.begin(), v.end());
    }
    sort(lhs.begin(), lhs.end());
    for (auto& v : rhs) {
        std::sort(v.begin(), v.end());
    }
    sort(rhs.begin(), rhs.end());
    return lhs == rhs;
}

TEST_CASE("4Sum") {
    TEST_SOLUTION(fourSum, v1) {
        vector<int> v = {};
        CHECK(equalVV(fourSum(v, 0), {}));

        v = {0};
        CHECK(equalVV(fourSum(v, 0), {}));

        v = {1, 0, -1, 0, -2, 2};
        CHECK(equalVV(
            fourSum(v, 0),
            vector<vector<int>>{{-1, 0, 0, 1}, {-2, -1, 1, 2}, {-2, 0, 0, 2}}));

        v = {-3, -2, -1, 0, 0, 1, 2, 3};
        CHECK(equalVV(fourSum(v, 0), vector<vector<int>>{{-3, -2, 2, 3},
                                                         {-3, -1, 1, 3},
                                                         {-3, 0, 0, 3},
                                                         {-3, 0, 1, 2},
                                                         {-2, -1, 0, 3},
                                                         {-2, -1, 1, 2},
                                                         {-2, 0, 0, 2},
                                                         {-1, 0, 0, 1}}));

        v = {1, 0, -1, 0, -2, 2};
        BENCHMARK("") { return fourSum(v, 0); };
    };
}

} // namespace four_sum
