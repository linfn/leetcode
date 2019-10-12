
/*
Validate Binary Search Tree

URL: https://leetcode.com/problems/validate-binary-search-tree
Tags: ['tree', 'depth-first-search']
___

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

  * The left subtree of a node contains only nodes with keys less than the node
's key.
  * The right subtree of a node contains only nodes with keys greater than the
node 's key.
  * Both the left and right subtrees must also be binary search trees.



Example 1:

        2
       / \
      1   3

    Input:  [2,1,3]
    Output: true


Example 2:

        5
       / \
      1   4
         / \
        3   6

    Input: [5,1,4,null,null,3,6]
    Output: false
    Explanation: The root node 's value is 5 but its right child's value is 4.
*/

#include <memory>
#include "test.h"

using namespace leetcode;

namespace validate_binary_search_tree {

inline namespace v1 {
using std::make_shared;
using std::shared_ptr;
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        int cur;
        bool first = true;
        return step(root, cur, first);
    }

private:
    bool step(TreeNode* root, int& cur, bool& first) {
        if (!root) {
            return true;
        }
        if (!step(root->left, cur, first)) {
            return false;
        }
        if (!first) {
            if (cur >= root->val) {
                return false;
            }
        } else {
            first = false;
        }
        cur = root->val;
        return step(root->right, cur, first);
    }
};
} // namespace v1

TEST_CASE("Validate Binary Search Tree") {
    TEST_SOLUTION(isValidBST, v1) {
        CHECK(isValidBST(makeTree({2, 1, 3})));
        CHECK_FALSE(isValidBST(makeTree({1, 1})));
        CHECK_FALSE(isValidBST(makeTree({10, 5, 15, 0, 0, 6, 20})));
    };
}

} // namespace validate_binary_search_tree
