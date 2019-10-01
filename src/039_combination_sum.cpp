
/*
Combination Sum

URL: https://leetcode.com/problems/combination-sum
Tags: ['array', 'backtracking']
___

Given a set of candidate numbers (`candidates`) (without duplicates) and a
target number (`target`), find all unique combinations in `candidates` where
the candidate numbers sums to `target`.

The same repeated number may be chosen from `candidates` unlimited number of
times.

Note:

  * All numbers (including `target`) will be positive integers.
  * The solution set must not contain duplicate combinations.

Example 1:

    Input: candidates = [2,3,6,7], target = 7,
    A solution set is:
    [
      [7],
      [2,2,3]
    ]


Example 2:

    Input: candidates = [2,3,5], target = 8,
    A solution set is:
    [
       [2,2,2,2],
      [2,3,3],
      [3,5]
    ]
*/

#include "test.h"

using std::vector;

namespace combination_sum {

/*
    backtracking 算法.
    要保证输出结果不重复, 只需保证每次输出的结果均为一个递增序列.
*/
inline namespace v1 {
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        if (candidates.empty()) {
            return result;
        }
        sort(candidates.begin(), candidates.end());
        vector<int> state;
        backtrack(state, 0, 0, candidates, target, result);
        return result;
    }

private:
    void backtrack(vector<int>& state, int sum, int begin,
                   const vector<int>& candidates, int target,
                   vector<vector<int>>& result) {
        if (sum > target) {
            return;
        }
        if (sum == target) {
            result.push_back(state);
            return;
        }
        for (int i = begin; i < candidates.size(); i++) {
            auto v = candidates[i];
            state.push_back(v);
            backtrack(state, sum + v, i, candidates, target, result);
            state.pop_back();
        }
    }
};
} // namespace v1

TEST_CASE("Combination Sum") {
    TEST_SOLUTION(combinationSum, v1) {
        vector<int> v = {2, 3, 6, 7};
        CHECK(combinationSum(v, 7) == vector<vector<int>>{{2, 2, 3}, {7}});
    };
}

} // namespace combination_sum
