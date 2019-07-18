/*
Two Sum

URL: https://leetcode.com/problems/two-sum
Tags: ['array', 'hash-table']
___

Given an array of integers, return indices of the two numbers such that they
add up to a specific target.

You may assume that each input would have exactly one solution, and you may
not use the same element twice.

Example:

    Given nums = [2, 7, 11, 15], target = 9,
    
    Because nums[ 0 ] + nums[ 1 ] = 2 + 7 = 9,
    return [ 0 , 1 ].
*/

#include <vector>
#include <map>
#include "catch.hpp"

using std::map;
using std::vector;

namespace two_sum {

namespace v1 {
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (auto i = 0; i < nums.size(); i++) {
            auto v = target - nums[i];
            for (auto ii = i + 1; ii < nums.size(); ii++) {
                if (nums[ii] == v) {
                    return {i, ii};
                }
            }
        }
        throw "no answer";
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> record;
        for (auto i = 0; i < nums.size(); i++) {
            auto v = target - nums[i];
            if (record.find(v) != record.end()) {
                return {record[v], i};
            }
            record.emplace(nums[i], i);
        }
        throw "no answer";
    }
};
} // namespace v2

TEST_CASE("Two Sum") {
    Solution s;

    vector<int> v = {1, 2, 3};
    REQUIRE(s.twoSum(v, 5) == vector<int>{1, 2});
}

} // namespace two_sum
