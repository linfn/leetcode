/*
Median of Two Sorted Arrays

URL: https://leetcode.com/problems/median-of-two-sorted-arrays
Tags: ['array', 'binary-search', 'divide-and-conquer']
___

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity
should be O(log (m+n)).

You may assume nums1 and nums2  cannot be both empty.

Example 1:

    nums1 = [1, 3]
    nums2 = [2]
    
    The median is 2.0


Example 2:

    nums1 = [1, 2]
    nums2 = [3, 4]
    
    The median is (2 + 3)/2 = 2.5
*/

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::sort;
using std::vector;

namespace median_of_two_sorted_arrays {

inline namespace v1 {
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        sort(nums1.begin(), nums1.end());
        if (nums1.size() % 2 == 1) {
            return nums1[nums1.size() / 2];
        } else {
            auto sum = nums1[nums1.size() / 2 - 1] + nums1[nums1.size() / 2];
            return sum / 2.0;
        }
    }
};
} // namespace v1

// TODO 更好的解决方案

TEST_CASE("Median of Two Sorted Arrays") {
    Solution s;

    auto nums1 = vector<int>{1, 3};
    auto nums2 = vector<int>{2};
    REQUIRE(s.findMedianSortedArrays(nums1, nums2) == 2.0);

    nums1 = vector<int>{1, 2};
    nums2 = vector<int>{3, 4};
    REQUIRE(s.findMedianSortedArrays(nums1, nums2) == (2 + 3) / 2.0);
}

} // namespace median_of_two_sorted_arrays
