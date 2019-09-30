
/*
Permutations II

URL: https://leetcode.com/problems/permutations-ii
Tags: ['backtracking']
___

Given a collection of numbers that might contain duplicates, return all
possible unique permutations.

Example:

    Input: [1,1,2]
    Output:
    [
      [1,1,2],
      [1,2,1],
      [2,1,1]
    ]
*/

#include "test.h"

using std::vector;

namespace permutations_ii {

/*
    在 046 的基础上 backtracking 时排除重复的就可以了
*/
inline namespace v1 {

using std::sort;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> state;
        state.reserve(nums.size());
        sort(nums.begin(), nums.end()); // 先排序
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
            if (i + 1 < remains.size()) {
                if (remains[i] == remains[i + 1]) {
                    continue;
                }
            }

            auto v = remains[i];
            state.push_back(v);
            remains.erase(remains.begin() + i);

            backtrack(state, remains, result);

            state.pop_back();
            remains.insert(remains.begin() + i, v);
        }
    }
};
} // namespace v1

TEST_CASE("Permutations II") {
    TEST_SOLUTION(permuteUnique, v1) {
        vector<int> v = {1, 1, 2};
        CHECK(permuteUnique(v) ==
              vector<vector<int>>{{1, 1, 2}, {1, 2, 1}, {2, 1, 1}});
    };
}

} // namespace permutations_ii
