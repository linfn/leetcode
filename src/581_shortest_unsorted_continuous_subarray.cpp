
/*
Shortest Unsorted Continuous Subarray

URL: https://leetcode.com/problems/shortest-unsorted-continuous-subarray
Tags: ['array']
___

Given an integer array, you need to find one continuous subarray that if you
only sort this subarray in ascending order, then the whole array will be
sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:

    Input: [2, 6, 4, 8, 10, 9, 15]
    Output: 5
    Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make
the whole array sorted in ascending order.


Note:

  1. Then length of the input array is in range [1, 10,000].
  2. The input array may contain duplicates, so ascending order here means < =.
*/

#include "test.h"

using std::vector;

namespace shortest_unsorted_continuous_subarray {

inline namespace v1 {
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int l = -1;
        for (int i = 1; i < nums.size(); i++) {
            if (l == -1 && nums[i] < nums[i - 1]) {
                l = i - 1;
            }
            while (l > 0 && nums[l - 1] > nums[i]) {
                l--;
            }
        }
        if (l == -1) {
            return 0;
        }
        int r = -1;
        for (int j = nums.size() - 2; j >= l; j--) {
            if (r == -1 && nums[j] > nums[j + 1]) {
                r = j + 1;
            }
            while (r != -1 && r < nums.size() - 1 && nums[r + 1] < nums[j]) {
                r++;
            }
        }
        return r - l + 1;
    }
};
} // namespace v1

TEST_CASE("Shortest Unsorted Continuous Subarray") {
    TEST_SOLUTION(findUnsortedSubarray, v1) {
        vector<int> v = {2, 6, 4, 8, 10, 9, 15};
        CHECK(findUnsortedSubarray(v) == 5);
        v = {1, 3, 2, 2, 2};
        CHECK(findUnsortedSubarray(v) == 4);
    };
}

} // namespace shortest_unsorted_continuous_subarray
