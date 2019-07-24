/*
Maximum Subarray

URL: https://leetcode.com/problems/maximum-subarray
Tags: ['array', 'divide-and-conquer', 'dynamic-programming']
___

Given an integer array `nums`, find the contiguous subarray (containing at
least one number) which has the largest sum and return its sum.

Example:

    Input: [-2,1,-3,4,-1,2,1,-5,4],
    Output: 6
    Explanation:  [4,-1,2,1] has the largest sum = 6.


Follow up:

If you have figured out the O( n ) solution, try coding another solution using
the divide and conquer approach, which is more subtle.
*/

#include <vector>
#include <cassert>

#include "test.h"

using std::max;
using std::vector;

namespace maximum_subarray {

inline namespace v1 {
// 动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        assert(!nums.empty());
        auto prev = nums[0];
        auto max = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (prev > 0) {
                prev = prev + nums[i];
            } else {
                prev = nums[i];
            }
            if (prev > max) {
                max = prev;
            }
        }
        return max;
    }
};
} // namespace v1

namespace v2 {
/*
分治方法. 将数组一分为二, 于是取值便有了三种可能:
左半的最值, 右半的最值, 或中间的最值(两个数组相连部分).

左右两半的最值用递归可以定义, 麻烦的是中间的最值, 它等于
左半数组从右边开始连续和的最大值 + 右半数组从左边开始连续和的最大值.

总之思路非常清奇. 但没 v1 快.
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        return step(nums.begin(), nums.end()).max;
    }

private:
    typedef vector<int>::iterator Iter;
    struct Result {
        int max;  // 连续和的最大值
        int lmax; // 从左边开始连续和的最大值
        int rmax; // 从右边开始连续和的最大值
        int sum;  // 数组的和
    };
    Result step(Iter begin, Iter end) {
        auto d = end - begin;
        if (d == 1) {
            auto v = *begin;
            return {v, v, v, v};
        }
        auto mid = begin + d / 2;
        auto lres = step(begin, mid), rres = step(mid, end);
        Result res;
        res.max = max(max(lres.max, rres.max), lres.rmax + rres.lmax);
        res.lmax = max(lres.lmax, lres.sum + rres.lmax);
        res.rmax = max(rres.rmax, rres.sum + lres.rmax);
        res.sum = lres.sum + rres.sum;
        return res;
    }
};
} // namespace v2

TEST_CASE("Maximum Subarray") {
    TEST_SOLUTION(maxSubArray, v1, v2) {
        vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        CHECK(maxSubArray(v) == 6);

        BENCHMARK("") { return maxSubArray(v); };
    };
}

} // namespace maximum_subarray
