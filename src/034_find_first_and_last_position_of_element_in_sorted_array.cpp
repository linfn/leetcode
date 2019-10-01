
/*
Find First and Last Position of Element in Sorted Array

URL:
https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
Tags: ['array', 'binary-search']
___

Given an array of integers `nums` sorted in ascending order, find the starting
and ending position of a given `target` value.

Your algorithm's runtime complexity must be in the order of O (log n ).

If the target is not found in the array, return `[-1, -1]`.

Example 1:

    Input: nums = [5,7,7,8,8,10], target = 8
    Output: [3,4]

Example 2:

    Input: nums = [5,7,7,8,8,10], target = 6
    Output: [-1,-1]
*/

#include "test.h"

using std::vector;

namespace find_first_and_last_position_of_element_in_sorted_array {

inline namespace v1 {
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return search(nums, 0, nums.size(), target);
    }

private:
    vector<int> search(const vector<int>& nums, int begin, int end,
                       int target) {
        if (begin == end) {
            return {-1, -1};
        }
        auto mid = begin + (end - begin) / 2;
        if (nums[mid] > target) {
            return search(nums, begin, mid, target);
        } else if (nums[mid] < target) {
            return search(nums, mid + 1, end, target);
        } else {
            return {searchStart(nums, begin, mid + 1, target),
                    searchEnd(nums, mid, end, target)};
        }
    }

    int searchStart(const vector<int>& nums, int begin, int end, int target) {
        auto mid = begin + (end - begin) / 2;
        if (nums[mid] != target) {
            return searchStart(nums, mid + 1, end, target);
        } else {
            if (mid == begin || nums[(mid - 1)] != target) {
                return mid;
            } else {
                return searchStart(nums, begin, mid, target);
            }
        }
    }
    int searchEnd(const vector<int>& nums, int begin, int end, int target) {
        auto mid = begin + (end - begin) / 2;
        if (nums[mid] != target) {
            return searchEnd(nums, begin, mid, target);
        } else {
            if (mid == end - 1 || nums[(mid + 1)] != target) {
                return mid;
            } else {
                return searchEnd(nums, mid + 1, end, target);
            }
        }
    }
};
} // namespace v1

TEST_CASE("Find First and Last Position of Element in Sorted Array") {
    TEST_SOLUTION(searchRange, v1) {
        vector<int> v = {5, 7, 7, 8, 8, 10};
        CHECK(searchRange(v, 8) == vector<int>{3, 4});
    };
}

} // namespace find_first_and_last_position_of_element_in_sorted_array
