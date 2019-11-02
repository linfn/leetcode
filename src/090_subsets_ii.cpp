
/*
Subsets II

URL: https://leetcode.com/problems/subsets-ii
Tags: ['array', 'backtracking']
___

Given a collection of integers that might contain duplicates, nums , return
all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

    Input: [1,2,2]
    Output:
    [
      [2],
      [1],
      [1,2,2],
      [2,2],
      [1,2],
      []
    ]
*/

#include "test.h"

using std::vector;

namespace subsets_ii {

/*
   沿用 078 subsets 中迭代的思路, 遇到重复的,
   上一步已经处理过的集合不用再处理了
*/
inline namespace v1 {
using std::move;
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        sort(nums.begin(), nums.end());
        int preEnd = 0;
        for (int i = 0; i < nums.size(); i++) {
            int start = 0;
            if (i > 0 && nums[i] == nums[i - 1]) {
                start = preEnd;
            }
            int end = result.size();
            for (int j = start; j < end; j++) {
                vector<int> item;
                item.reserve(result[j].size() + 1);
                item.insert(item.end(), result[j].begin(), result[j].end());
                item.push_back(nums[i]);
                result.push_back(move(item));
            }
            preEnd = end;
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Subsets II") {
    TEST_SOLUTION(subsetsWithDup, v1) {
        using namespace leetcode;
        vector<int> v = {1, 2, 2};
        CHECK(unorderedEqual(
            subsetsWithDup(v),
            vector<vector<int>>{{}, {1}, {2}, {1, 2}, {1, 2, 2}, {2, 2}}));
    };
}

} // namespace subsets_ii
