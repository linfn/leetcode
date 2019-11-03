
/*
Invert Binary Tree

URL: https://leetcode.com/problems/invert-binary-tree
Tags: ['tree']
___

Invert a binary tree.

Example:

Input:



         4
       /   \
      2     7
     / \   / \
    1   3 6   9

Output:



         4
       /   \
      7     2
     / \   / \
    9   6 3   1

Trivia:
This problem was inspired by [this original
tweet](https://twitter.com/mxcl/status/608682016205344768) by [Max
Howell](https://twitter.com/mxcl):

> Google: 90% of our engineers use the software you wrote (Homebrew), but you
can't invert a binary tree on a whiteboard so f*** off.
*/

#include "test.h"

using namespace leetcode;

namespace invert_binary_tree {

inline namespace v1 {
using std::swap;
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) {
            return nullptr;
        }
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
} // namespace v1

TEST_CASE("Invert Binary Tree") {
    TEST_SOLUTION(invertTree, v1) {
        CHECK(treeEqual(invertTree(makeTree({4, 2, 7, 1, 3, 6, 9})),
                        makeTree({4, 7, 2, 9, 6, 3, 1})));
    };
}

} // namespace invert_binary_tree
