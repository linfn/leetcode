
/*
Diameter of Binary Tree

URL: https://leetcode.com/problems/diameter-of-binary-tree
Tags: ['tree']
___

Given a binary tree, you need to compute the length of the diameter of the
tree. The diameter of a binary tree is the length of the longest path between
any two nodes in a tree. This path may or may not pass through the root.

Example:

Given a binary tree



              1
             / \
            2   3
           / \
          4   5


Return 3 , which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of
edges between them.
*/

#include "test.h"

using namespace leetcode;

namespace diameter_of_binary_tree {

/*
    在 dfs 求树高的过程中, 解决最长路径的问题
*/
inline namespace v1 {
using std::max;
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int nodes = 0;
        depth(root, nodes);
        return nodes - 1;
    }

private:
    int depth(TreeNode* root, int& result) {
        if (!root) {
            return 0;
        }
        int left = depth(root->left, result);
        int right = depth(root->right, result);
        result = max(result, left + right + 1);
        return max(left, right) + 1;
    }
};
} // namespace v1

TEST_CASE("Diameter of Binary Tree") {
    TEST_SOLUTION(diameterOfBinaryTree, v1) {
        CHECK(diameterOfBinaryTree(makeTree({1, 2, 3, 4, 5})) == 3);
    };
}

} // namespace diameter_of_binary_tree
