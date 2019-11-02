
/*
Subsets

URL: https://leetcode.com/problems/subsets
Tags: ['array', 'backtracking', 'bit-manipulation']
___

Given a set of distinct integers, nums , return all possible subsets (the
power set).

Note: The solution set must not contain duplicate subsets.

Example:

    Input: nums = [1,2,3]
    Output:
    [
      [3],
      [1],
      [2],
      [1,2,3],
      [1,3],
      [2,3],
      [1,2],
      []
    ]
*/

#include "test.h"

using std::vector;

namespace subsets {

namespace v1 {
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> item;
        for (int n = 0; n <= nums.size(); n++) {
            subsetsN(nums, 0, n, item, result);
        }
        return result;
    }

private:
    void subsetsN(const vector<int>& nums, int begin, int n, vector<int>& item,
                  vector<vector<int>>& result) {
        if (n == 0) {
            result.push_back(item);
            return;
        }
        for (int i = begin; i < (nums.size() - n + 1); i++) {
            item.push_back(nums[i]);
            subsetsN(nums, i + 1, n - 1, item, result);
            item.pop_back();
        }
    }
};
} // namespace v1

/*
    backtracing
*/
namespace v2 {
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> item;
        backtrace(nums, 0, item, result);
        return result;
    }

private:
    void backtrace(const vector<int>& nums, int begin, vector<int>& item,
                   vector<vector<int>>& result) {
        result.push_back(item);
        for (int i = begin; i < nums.size(); i++) {
            item.push_back(nums[i]);
            backtrace(nums, i + 1, item, result);
            item.pop_back();
        }
    }
};
} // namespace v2

/*
    Iterative:
    1. 初始: [[]]
    2. 添加 1 到结果集: [[], [1]];
    3. 添加 2 到结果集: [[], [1], [2], [1, 2]];
    4. 添加 3 到结果集: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]].
*/
inline namespace v3 {
using std::move;
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        for (auto n : nums) {
            int size = result.size();
            for (int i = 0; i < size; i++) {
                vector<int> item;
                item.reserve(result[i].size() + 1);
                item.insert(item.end(), result[i].begin(), result[i].end());
                item.push_back(n);
                result.emplace_back(move(item));
            }
        }
        return result;
    }
};
} // namespace v3

/*
    Bit Manipulation, 把每一个数字看作一位, 1 取, 0 不取.
*/
namespace v4 {
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> item;
        int n = 1 << nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i & (1 << j)) {
                    item.push_back(nums[j]);
                }
            }
            result.push_back(item);
            item.clear();
        }
        return result;
    }
};
} // namespace v4

TEST_CASE("Subsets") {
    TEST_SOLUTION(subsets, v1, v2, v3, v4) {
        using namespace leetcode;
        vector<int> v = {1, 2, 3};
        CHECK(unorderedEqual(
            subsets(v),
            vector<vector<int>>{
                {}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}));
    };
}

} // namespace subsets
