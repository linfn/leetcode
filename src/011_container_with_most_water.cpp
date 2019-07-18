/*
Container With Most Water

URL: https://leetcode.com/problems/container-with-most-water
Tags: ['array', 'two-pointers']
___

Given n non-negative integers a 1, a 2, ..., a n , where each represents a
point at coordinate ( i , a i). n vertical lines are drawn such that the two
endpoints of line i is at ( i , a i) and ( i , 0). Find two lines, which
together with x-axis forms a container, such that the container contains the
most water.

Note:  You may not slant the container and n is at least 2.



![](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this
case, the max area of water (blue section) the container can contain is 49.



Example:

    Input: [1,8,6,2,5,4,8,3,7]
    Output: 49
*/

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

namespace container_with_most_water {

inline namespace v1 {
// 思路: 从最两边开始, 向中间逼近.
// 要想找到下个比当前大的结果, 就要找到比当前最矮边更高的一边.
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0, left = 0, right = height.size() - 1;
        while (left < right) {
            int w = right - left, h;
            if (height[left] < height[right]) {
                h = height[left];
                left++;
            } else {
                h = height[right];
                right--;
            }
            int area = w * h;
            if (area > max) {
                max = area;
            }
        }
        return max;
    }
};
} // namespace v1

TEST_CASE("Container With Most Water") {
    Solution s;
    vector<int> v = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    CHECK(s.maxArea(v) == 49);
}

} // namespace container_with_most_water
