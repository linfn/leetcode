
/*
Kth Largest Element in an Array

URL: https://leetcode.com/problems/kth-largest-element-in-an-array
Tags: ['divide-and-conquer', 'heap']
___

Find the k th largest element in an unsorted array. Note that it is the kth
largest element in the sorted order, not the kth distinct element.

Example 1:

    Input: [3,2,1,5,6,4] and k = 2
    Output: 5


Example 2:

    Input: [3,2,3,1,2,4,5,5,6] and k = 4
    Output: 4

Note:
You may assume k is always valid, 1  ≤ k ≤ array's length.
*/

#include "test.h"

using std::vector;

namespace kth_largest_element_in_an_array {

namespace v1 {
using std::make_heap;
using std::pop_heap;
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        make_heap(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++) {
            pop_heap(nums.begin(), nums.end() - i);
        }
        return nums.front();
    }
};
} // namespace v1

/*
    Partial sorting, 和快速排序的过程相似
*/
inline namespace v2 {
using std::greater;
using std::nth_element;
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(),
                    greater<>());
        return nums[k - 1];
    }
};
} // namespace v2

TEST_CASE("Kth Largest Element in an Array") {
    TEST_SOLUTION(findKthLargest, v1, v2) {
        vector<int> v = {3, 2, 1, 5, 6, 4};
        CHECK(findKthLargest(v, 2) == 5);
    };
}

} // namespace kth_largest_element_in_an_array
