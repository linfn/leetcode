
/*
Remove Duplicates from Sorted Array

URL: https://leetcode.com/problems/remove-duplicates-from-sorted-array
Tags: ['array', 'two-pointers']
___

Given a sorted array nums , remove the duplicates [in-
place](https://en.wikipedia.org/wiki/In-place_algorithm) such that each
element appear only once and return the new length.

Do not allocate extra space for another array, you must do this by modifying
the input array[in-place](https://en.wikipedia.org/wiki/In-place_algorithm)
with O(1) extra memory.

Example 1:

    Given nums = [1,1,2] ,

    Your function should return length = 2 , with the first two elements of nums
being 1 and 2 respectively.

    It doesn 't matter what you leave beyond the returned length.

Example 2:

    Given nums = [0,0,1,1,1,2,2,3,3,4] ,

    Your function should return length = 5 , with the first five elements of
nums being modified to   0 , 1 , 2 , 3 , and  4 respectively.

    It doesn 't matter what values are set beyond the returned length.


Clarification:

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by reference , which means modification
to the input array will be known to the caller as well.

Internally you can think of this:

    // nums is passed in by reference. (i.e., without making a copy)
    int len = removeDuplicates(nums);

    // any modification to nums in your function would be known by the caller.
    // using the length returned by your function, it prints the first len
elements. for (int i = 0; i  < len; i++) { print(nums[i]);
    }
*/

#include <vector>
#include <algorithm>

#include "test.h"

using std::swap;
using std::unique;
using std::vector;

namespace remove_duplicates_from_sorted_array {

namespace v1 {
// 一行流
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return unique(nums.begin(), nums.end()) - nums.begin();
    }
};
} // namespace v1

namespace v2 {
// 这个版本每次删除时会移动后面的所有元素, 效率不好
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int cur = nums.front();
        for (int i = 1; i < nums.size();) {
            if (nums[i] == cur) {
                // 这里会拷贝后面所有元素
                nums.erase(nums.begin() + i);
            } else {
                cur = nums[i];
                i++;
            }
        }
        return nums.size();
    }
};
} // namespace v2

inline namespace v3 {
/*
two-pointers 解法:
`i` 始终指向不重复的部分的结尾, `j` 不断向后迭代, `(i, j)` 这部分都是重复的元素
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {
                i++;
                swap(nums[j], nums[i]);
            }
        }
        return i + 1;
    }
};
} // namespace v3

TEST_CASE("Remove Duplicates from Sorted Array") {
    TEST_SOLUTION(removeDuplicates, v1, v2, v3) {
        vector<int> v = {1, 1, 2};
        int size = removeDuplicates(v);
        CHECK(vector<int>{v.begin(), v.begin() + size} == vector<int>{1, 2});

        v = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        size = removeDuplicates(v);
        CHECK(vector<int>{v.begin(), v.begin() + size} ==
              vector<int>{0, 1, 2, 3, 4});

        BENCHMARK("") {
            vector<int> v = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
            return removeDuplicates(v);
        };
    };
}

} // namespace remove_duplicates_from_sorted_array
