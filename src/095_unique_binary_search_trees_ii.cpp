/*
Unique Binary Search Trees II

URL: https://leetcode.com/problems/unique-binary-search-trees-ii
Tags: ['dynamic-programming', 'tree']
___

Given an integer n , generate all structurally unique BST 's (binary search
trees) that store values 1 ...  n.

Example:

    Input: 3
    Output:
    [
       [1,null,3,2],
      [3,2,null,1],
      [3,1,null,null,2],
      [2,1,3],
      [1,null,2,null,3]
    ]
    Explanation:
    The above output corresponds to the 5 unique BST 's shown below:
    
       1         3     3      2      1
        \       /     /      / \      \
         3     2     1      1   3      2
        /     /       \                 \
       2     1         2                 3
*/

#include <vector>
#include "catch.hpp"

using std::vector;

namespace unique_binary_search_trees_ii {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

inline namespace v1 {
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) { return step(1, n); }

private:
    // 这个递归的特点在于, 必须先计算得到子步骤的结果, 才能计算自己当前的结果.
    // 每一步都返回自己当前所有可能的结果方案.
    vector<TreeNode*> step(int begin, int end) {
        vector<TreeNode*> result;
        for (auto i = begin; i <= end; i++) {
            // 计算所有左边可能的结果
            auto lefts = step(begin, i - 1);
            if (lefts.empty()) { // 没有结果时可以选择为空
                lefts.push_back(nullptr);
            }
            // 计算所有右边可能的结果
            auto rights = step(i + 1, end);
            if (rights.empty()) { // 没有结果时可以选择为空
                rights.push_back(nullptr);
            }
            for (auto l : lefts) {
                for (auto r : rights) {
                    auto node = new TreeNode(i);
                    node->left = l;
                    node->right = r;
                    result.push_back(node);
                }
            }
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Unique Binary Search Trees II") {
    // TODO 完善 test case
    Solution s;
    CHECK(s.generateTrees(3).size() == 5);
}

} // namespace unique_binary_search_trees_ii
