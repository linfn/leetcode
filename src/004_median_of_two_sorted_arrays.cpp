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

#include "test.h"

using std::sort;
using std::vector;

namespace median_of_two_sorted_arrays {

inline namespace v1 {
/*
这个方案的思路是两个有序数组的排序, 但不符合 O(log (m+n)) 的要求
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1, n2;
        const auto push = [&](int n) {
            n1 = n2;
            n2 = n;
        };
        int size = (nums1.size() + nums2.size()) / 2 + 1;
        for (int i = 0, j = 0; i + j < size;) {
            if (j >= nums2.size() ||
                (i < nums1.size() && nums1[i] < nums2[j])) {
                push(nums1[i]);
                i++;
            } else {
                push(nums2[j]);
                j++;
            }
        }
        if ((nums1.size() + nums2.size()) % 2 == 1) {
            return n2;
        } else {
            return (n1 + n2) / 2.0;
        }
    }
};
} // namespace v1

// TODO 更好的解决方案

TEST_CASE("Median of Two Sorted Arrays") {
    TEST_SOLUTION(findMedianSortedArrays, v1) {
        vector<int> nums1 = {1, 3}, nums2 = {2};
        CHECK(findMedianSortedArrays(nums1, nums2) == 2.0);
        nums1 = {2}, nums2 = {};
        CHECK(findMedianSortedArrays(nums1, nums2) == 2.0);
        nums1 = {1, 2}, nums2 = {3, 4};
        CHECK(findMedianSortedArrays(nums1, nums2) == (2 + 3) / 2.0);

        BENCHMARK("") { return findMedianSortedArrays(nums1, nums2); };
    };
}

} // namespace median_of_two_sorted_arrays
