/*
Search in Rotated Sorted Array

URL: https://leetcode.com/problems/search-in-rotated-sorted-array
Tags: ['array', 'binary-search']
___

Suppose an array sorted in ascending order is rotated at some pivot unknown to
you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its
index, otherwise return `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of  O (log  n ).

Example 1:

    Input: nums = [4,5,6,7,0,1,2], target = 0
    Output: 4


Example 2:

    Input: nums = [4,5,6,7,0,1,2], target = 3
    Output: -1
*/

#include "test.h"

using std::vector;

namespace search_in_rotated_sorted_array {

inline namespace v1 {
// 思路依然是二分查找
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return bsearch(target, nums, 0, int(nums.size()) - 1);
    }

private:
    int bsearch(int target, const vector<int>& nums, int begin, int end) {
        if (begin > end) {
            return -1;
        }
        auto med = begin + ((end - begin) / 2);
        if (nums[med] == target) {
            return med;
        } else {
            // 首先要判断当前分支是否包含转换点
            if (nums[begin] < nums[end]) {
                // 如果当前分支不包含转换点,
                // 那搜索过程就是正常的有序数组二分查找法
                if (nums[med] > target) {
                    return bsearch(target, nums, begin, med - 1);
                } else {
                    return bsearch(target, nums, med + 1, end);
                }
            } else {
                // 如果当前分支包含转换点,
                // 则无法直接判断应该选择哪一边的分支, 所以两边分支都进行尝试
                auto i = bsearch(target, nums, begin, med - 1);
                if (i != -1) {
                    return i;
                }
                return bsearch(target, nums, med + 1, end);
            }
        }
    }
};
} // namespace v1

TEST_CASE("Search in Rotated Sorted Array") {
    TEST_SOLUTION(search, v1) {
        vector<int> v{4, 5, 6, 7, 0, 1, 2};
        CHECK(search(v, 0) == 4);
        v = vector<int>{4, 5, 6, 7, 0, 1, 2};
        CHECK(search(v, 3) == -1);

        BENCHMARK("") { return search(v, 3); };
    };
}

} // namespace search_in_rotated_sorted_array
