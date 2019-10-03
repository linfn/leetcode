
/*
First Missing Positive

URL: https://leetcode.com/problems/first-missing-positive
Tags: ['array']
___

Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

    Input: [1,2,0]
    Output: 3


Example 2:

    Input: [3,4,-1,1]
    Output: 2


Example 3:

    Input: [7,8,9,11,12]
    Output: 1


Note:

Your algorithm should run in O ( n ) time and uses constant extra space.
*/

#include "test.h"

using std::vector;

namespace first_missing_positive {

/*
    思路就是把每一个数放到它该放的位置
*/
inline namespace v1 {

using std::swap;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= nums.size()) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};
} // namespace v1

TEST_CASE("First Missing Positive") {
    TEST_SOLUTION(firstMissingPositive, v1) {
        vector<int> v = {1, 2, 0};
        CHECK(firstMissingPositive(v) == 3);

        v = {3, 4, -1, 1};
        CHECK(firstMissingPositive(v) == 2);

        v = {7, 8, 9, 11, 12};
        CHECK(firstMissingPositive(v) == 1);
    };
}

} // namespace first_missing_positive
