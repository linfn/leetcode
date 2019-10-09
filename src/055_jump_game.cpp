
/*
Jump Game

URL: https://leetcode.com/problems/jump-game
Tags: ['array', 'greedy']
___

Given an array of non-negative integers, you are initially positioned at the
first index of the array.

Each element in the array represents your maximum jump length at that
position.

Determine if you are able to reach the last index.

Example 1:

    Input: [2,3,1,1,4]
    Output: true
    Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.


Example 2:

    Input: [3,2,1,0,4]
    Output: false
    Explanation: You will always arrive at index 3 no matter what. Its maximum
                  jump length is 0, which makes it impossible to reach the last
index.
*/

#include "test.h"

using std::vector;

namespace jump_game {

/*
    Time Limit Exceeded.
    主要思路就是倒过来走, 复用之前计算的结果.
*/
namespace v1 {
class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> cache(nums.size());
        cache.back() = true;
        for (int i = nums.size() - 2; i >= 0; i--) {
            bool can = false;
            for (int j = nums[i]; j > 0; j--) {
                if (i + j >= nums.size() || cache[i + j]) {
                    can = true;
                    break;
                }
            }
            cache[i] = can;
        }
        return cache.front();
    }
};
} // namespace v1

/*
    能否到达终点取决于能否越过所有 0 点.
*/
inline namespace v2 {
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int max = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == 0 && max <= i) {
                return false;
            }
            int idx = i + nums[i];
            if (idx > max) {
                max = idx;
            }
        }
        return true;
    }
};
} // namespace v2

TEST_CASE("Jump Game") {
    TEST_SOLUTION(canJump, v1) {
        vector<int> v = {2, 3, 1, 1, 4};
        CHECK(canJump(v));

        v = {3, 2, 1, 0, 4};
        CHECK_FALSE(canJump(v));

        v = {0};
        CHECK(canJump(v));
    };
}

} // namespace jump_game
