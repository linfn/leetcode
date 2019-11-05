
/*
Merge Two Binary Trees

URL: https://leetcode.com/problems/merge-two-binary-trees
Tags: ['tree']
___

Given two binary trees and imagine that when you put one of them to cover the
other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two
nodes overlap, then sum node values up as the new value of the merged node.
Otherwise, the NOT null node will be used as the node of new tree.

Example 1:

    Input:
        Tree 1                     Tree 2
              1                         2
             / \                       / \
            3   2                     1   3
           /                           \   \
          5                             4   7
    Output:
    Merged tree:
             3
            / \
           4   5
          / \   \
         5   4   7




Note: The merging process must start from the root nodes of both trees.
*/

#include <array>

#include "test.h"

using namespace leetcode;

namespace merge_two_binary_trees {

namespace v1 {
using std::array;
using std::deque;
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) {
            return nullptr;
        }
        auto root = new TreeNode(0);
        deque<array<TreeNode*, 3>> que;
        que.push_back({root, t1, t2});
        while (!que.empty()) {
            const auto& front = que.front();
            array<TreeNode*, 3> itemLeft = {0, 0, 0}, itemRight = {0, 0, 0};
            if (front[1]) {
                front[0]->val = front[1]->val;
                itemLeft[1] = front[1]->left;
                itemRight[1] = front[1]->right;
            }
            if (front[2]) {
                front[0]->val += front[2]->val;
                itemLeft[2] = front[2]->left;
                itemRight[2] = front[2]->right;
            }
            if (itemLeft[1] || itemLeft[2]) {
                itemLeft[0] = new TreeNode(0);
                front[0]->left = itemLeft[0];
                que.push_back(itemLeft);
            }
            if (itemRight[1] || itemRight[2]) {
                itemRight[0] = new TreeNode(0);
                front[0]->right = itemRight[0];
                que.push_back(itemRight);
            }
            que.pop_front();
        }
        return root;
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1) {
            return t2; // 如果一支为空, 则合并结果直接等于另一支
        } else if (!t2) {
            return t1;
        }
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
};
} // namespace v2

TEST_CASE("Merge Two Binary Trees") {
    TEST_SOLUTION(mergeTrees, v1, v2) {
        CHECK(treeEqual(
            mergeTrees(makeTree({1, 3, 2, 5}), makeTree({2, 1, 3, 0, 4, 0, 7})),
            makeTree({3, 4, 5, 5, 4, 0, 7})));
    };
}

} // namespace merge_two_binary_trees
