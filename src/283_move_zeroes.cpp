
/*
Move Zeroes

URL: https://leetcode.com/problems/move-zeroes
Tags: ['array', 'two-pointers']
___

Given an array `nums`, write a function to move all `0`'s to the end of it
while maintaining the relative order of the non-zero elements.

Example:

    Input: [0,1,0,3,12]
    Output: [1,3,12,0,0]

Note :

  1. You must do this in-place without making a copy of the array.
  2. Minimize the total number of operations.
*/

#include "test.h"

using std::vector;

namespace move_zeroes {

inline namespace v1 {
using std::swap;
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroStart = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (zeroStart != -1) {
                    swap(nums[zeroStart], nums[i]);
                    zeroStart++;
                }
            } else {
                if (zeroStart == -1) {
                    zeroStart = i;
                }
            }
        }
    }
};
} // namespace v1

TEST_CASE("Move Zeroes") {
    TEST_SOLUTION(moveZeroes, v1) {
        vector<int> v = {0, 1, 0, 3, 12};
        moveZeroes(v);
        CHECK(v == vector<int>{1, 3, 12, 0, 0});
    };
}

} // namespace move_zeroes
