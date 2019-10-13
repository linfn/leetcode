
/*
Binary Tree Level Order Traversal

URL: https://leetcode.com/problems/binary-tree-level-order-traversal
Tags: ['tree', 'breadth-first-search']
___

Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,



        3
       / \
      9  20
        /  \
       15   7


return its level order traversal as:



    [
      [3],
      [9,20],
      [15,7]
    ]
*/

#include "test.h"

using namespace leetcode;
using std::vector;

namespace binary_tree_level_order_traversal {

/*
    BFS 遍历适合用一个队列维护状态,
    这题主要是在如何分割 level 上.
*/
inline namespace v1 {
using std::deque;
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }
        deque<TreeNode*> deq = {root, nullptr};
        while (deq.front()) {
            vector<int> v;
            for (;;) {
                auto n = deq.front();
                deq.pop_front();
                if (!n) {
                    break;
                }
                v.push_back(n->val);
                if (n->left) {
                    deq.push_back(n->left);
                }
                if (n->right) {
                    deq.push_back(n->right);
                }
            }
            result.emplace_back(move(v));
            deq.push_back(nullptr);
        }
        return result;
    }
};
} // namespace v1

TEST_CASE("Binary Tree Level Order Traversal") {
    TEST_SOLUTION(levelOrder, v1) {
        CHECK(levelOrder(makeTree({3, 9, 20, 0, 0, 15, 7})) ==
              vector<vector<int>>{{3}, {9, 20}, {15, 7}});
    };
}

} // namespace binary_tree_level_order_traversal
