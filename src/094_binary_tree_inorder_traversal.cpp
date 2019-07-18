/*
Binary Tree Inorder Traversal

URL: https://leetcode.com/problems/binary-tree-inorder-traversal
Tags: ['hash-table', 'stack', 'tree']
___

Given a binary tree, return the inorder traversal of its nodes ' values.

Example:

    Input: [1,null,2,3]
       1
        \
         2
        /
       3
    
    Output: [1,3,2]

Follow up: Recursive solution is trivial, could you do it iteratively?
*/

#include <vector>
#include <stack>
#include "catch.hpp"

using std::stack;
using std::vector;

namespace binary_tree_inorder_traversal {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

namespace v1 {
// NOTE: 题目要求用迭代而不是递归, 所以 v1 方案不符合要求
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        step(result, root);
        return result;
    }

private:
    void step(vector<int>& v, TreeNode* node) {
        if (!node) {
            return;
        }
        step(v, node->left);
        v.push_back(node->val);
        step(v, node->right);
    }
};
} // namespace v1

inline namespace v2 {
// 使用迭代方式遍历二叉树的要点是用一个 stack 来记录中间状态
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        auto node = root;
        for (;;) {
            if (node) {
                st.push(node);
                node = node->left;
            } else {
                if (st.empty()) {
                    break;
                }
                node = st.top();
                st.pop();
                result.push_back(node->val);
                node = node->right;
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("Binary Tree Inorder Traversal") {
    Solution s;

    auto root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);

    CHECK(s.inorderTraversal(root) == vector<int>{1, 3, 2});
}

} // namespace binary_tree_inorder_traversal
