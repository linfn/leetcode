
/*
Sort Colors

URL: https://leetcode.com/problems/sort-colors
Tags: ['array', 'two-pointers', 'sort']
___

Given an array with n objects colored red, white or blue, sort them [in-
place](https://en.wikipedia.org/wiki/In-place_algorithm)  so that objects of
the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white,
and blue respectively.

Note:  You are not suppose to use the library's sort function for this
problem.

Example:

    Input: [2,0,2,1,1,0]
    Output: [0,0,1,1,2,2]

Follow up:

  * A rather straight forward solution is a two-pass algorithm using counting
sort. First, iterate the array counting number of 0's, 1's, and 2's, then
overwrite array with total number of 0's, then 1's and followed by 2's.

  * Could you come up with a one-pass algorithm using only constant space?
*/

#include "test.h"

using std::vector;

namespace sort_colors {

inline namespace v1 {
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int red = 0, white = 0;
        for (int i = 0; i < nums.size(); i++) {
            int v = nums[i];
            nums[i] = 2;
            if (v < 2) {
                nums[white] = 1;
                white++;
            }
            if (v < 1) {
                nums[red] = 0;
                red++;
            }
        }
    }
};
} // namespace v1

TEST_CASE("Sort Colors") {
    TEST_SOLUTION(sortColors, v1) {
        vector<int> v = {2, 0, 2, 1, 1, 0};
        sortColors(v);
        CHECK(v == vector<int>{0, 0, 1, 1, 2, 2});
    };
}

} // namespace sort_colors
