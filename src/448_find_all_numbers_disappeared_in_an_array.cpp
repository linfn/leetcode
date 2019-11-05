
/*
Find All Numbers Disappeared in an Array

URL: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array
Tags: ['array']
___

Given an array of integers where 1 ≤ a[i] ≤ n ( n = size of array), some
elements appear twice and others appear once.

Find all the elements of [1, n ] inclusive that do not appear in this array.

Could you do it without extra space and in O( n ) runtime? You may assume the
returned list does not count as extra space.

Example:

    Input:
    [4,3,2,7,8,2,3,1]

    Output:
    [5,6]
*/

#include "test.h"

using std::vector;

namespace find_all_numbers_disappeared_in_an_array {

/*
    和 41 first_missing_positive 思路一样, 就是把数字放到该放的地方去
*/
inline namespace v1 {
using std::swap;
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size();) {
            auto n = nums[i];
            if (n != 0 && n != i + 1) {
                if (nums[n - 1] != n) {
                    swap(nums[i], nums[n - 1]);
                } else {
                    nums[i] = 0;
                    i++;
                }
            } else {
                i++;
            }
        }
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                result.push_back(i + 1);
            }
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Find All Numbers Disappeared in an Array") {
    TEST_SOLUTION(findDisappearedNumbers, v1) {
        vector<int> v = {4, 3, 2, 7, 8, 2, 3, 1};
        CHECK(findDisappearedNumbers(v) == vector<int>{5, 6});
    };
}

} // namespace find_all_numbers_disappeared_in_an_array
