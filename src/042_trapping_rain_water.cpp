
/*
Trapping Rain Water

URL: https://leetcode.com/problems/trapping-rain-water
Tags: ['array', 'two-pointers', 'stack']
___

Given n non-negative integers representing an elevation map where the width of
each bar is 1, compute how much water it is able to trap after raining.

![](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)
The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In
this case, 6 units of rain water (blue section) are being trapped. Thanks
Marcos for contributing this image!

Example:

    Input: [0,1,0,2,1,0,1,3,2,1,2,1]
    Output: 6
*/

#include "test.h"

using std::vector;

namespace trapping_rain_water {

/*
    左右往中间的最高处逼近.
*/
inline namespace v1 {
class Solution {
public:
    int trap(vector<int>& height) {
        int result = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    result += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    result += rightMax - height[right];
                }
                right--;
            }
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Trapping Rain Water") {
    TEST_SOLUTION(trap, v1) {
        vector<int> v = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        CHECK(trap(v) == 6);
    };
}

} // namespace trapping_rain_water
