
/*
Maximum Depth of Binary Tree

URL: https://leetcode.com/problems/maximum-depth-of-binary-tree
Tags: ['tree', 'depth-first-search']
___

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

Note:  A leaf is a node with no children.

Example:

Given binary tree `[3,9,20,null,null,15,7]`,

        3
       / \
      9  20
        /  \
       15   7

return its depth = 3.
*/

#include "test.h"

using namespace leetcode;

namespace maximum_depth_of_binary_tree {

inline namespace v1 {

using std::max;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
} // namespace v1

TEST_CASE("Maximum Depth of Binary Tree") {
    TEST_SOLUTION(maxDepth, v1) {
        CHECK(maxDepth(makeTree({3, 9, 20, 0, 0, 15, 7})) == 3);
    };
}

} // namespace maximum_depth_of_binary_tree
