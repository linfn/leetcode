
/*
Permutations

URL: https://leetcode.com/problems/permutations
Tags: ['backtracking']
___

Given a collection of distinct integers, return all possible permutations.

Example:

    Input: [1,2,3]
    Output:
    [
      [1,2,3],
      [1,3,2],
      [2,1,3],
      [2,3,1],
      [3,1,2],
      [3,2,1]
    ]
*/

#include "test.h"

using std::vector;

namespace permutations {

/*
    使用 031 中 nextPermutation 的方法来逐个生成.
*/
inline namespace v1 {

using std::reverse;
using std::swap;
using std::upper_bound;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result = {nums};
        for (next(nums); nums != result[0]; next(nums)) {
            result.push_back(nums);
        }
        return result;
    }

private:
    void next(vector<int>& nums) {
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

/*
    使用 backtracking 来遍历所有可能的结果.
*/
namespace v2 {
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> state;
        state.reserve(nums.size());
        backtrack(state, nums, result);
        return result;
    }

private:
    void backtrack(vector<int>& state, vector<int>& remains,
                   vector<vector<int>>& result) {
        if (remains.empty()) {
            result.push_back(state);
            return;
        }
        for (int i = 0; i < remains.size(); i++) {
            auto v = remains[i];
            state.push_back(v);
            remains.erase(remains.begin() + i);

            backtrack(state, remains, result);

            state.pop_back();
            remains.insert(remains.begin() + i, v);
        }
    }
};
} // namespace v2

TEST_CASE("Permutations") {
    TEST_SOLUTION(permute, v1, v2) {
        vector<int> v = {1, 2, 3};
        CHECK(permute(v) == vector<vector<int>>{{1, 2, 3},
                                                {1, 3, 2},
                                                {2, 1, 3},
                                                {2, 3, 1},
                                                {3, 1, 2},
                                                {3, 2, 1}});

        BENCHMARK("") {
            vector<int> v = {1, 2, 3};
            return permute(v);
        };
    };
}

} // namespace permutations
