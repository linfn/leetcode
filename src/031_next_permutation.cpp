
/*
Next Permutation

URL: https://leetcode.com/problems/next-permutation
Tags: ['array']
___

Implement next permutation , which rearranges numbers into the
lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest
possible order (ie, sorted in ascending order).

The replacement must be [in-place](http://en.wikipedia.org/wiki/In-
place_algorithm) and use only constant  extra memory.

Here are some examples. Inputs are in the left-hand column and its
corresponding outputs are in the right-hand column.

`1,2,3` -> `1,3,2`
`3,2,1` -> `1,2,3`
`1,1,5` -> `1,5,1`
*/

#include "test.h"

using std::reverse;
using std::swap;
using std::upper_bound;
using std::vector;

namespace next_permutation {

/*
    每一次都生成一个比当前数大一点的数, 以此来遍历所有可能的排列.
*/
inline namespace v1 {
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                swap(nums[i],
                     *upper_bound(nums.rbegin(), nums.rend() - i - 1, nums[i]));
                reverse(nums.begin() + i + 1, nums.end());
                return;
            }
        }
        reverse(nums.begin(), nums.end());
    }
};
} // namespace v1

TEST_CASE("Next Permutation") {
    TEST_SOLUTION(nextPermutation, v1) {
        vector<int> v = {1, 2, 3};
        nextPermutation(v);
        CHECK(v == vector<int>{1, 3, 2});

        v = {3, 2, 1};
        nextPermutation(v);
        CHECK(v == vector<int>{1, 2, 3});

        v = {1, 1, 5};
        nextPermutation(v);
        CHECK(v == vector<int>{1, 5, 1});

        v = {1, 3, 2};
        nextPermutation(v);
        CHECK(v == vector<int>{2, 1, 3});

        v = {5, 1, 1};
        nextPermutation(v);
        CHECK(v == vector<int>{1, 1, 5});
    };
}

} // namespace next_permutation
