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

#include "test.h"

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
        if (!root) {
            return result;
        }
        stack<TreeNode*> st;
        st.push(root);
        bool goleft = true;
        while (!st.empty()) {
            auto cur = st.top();
            if (goleft) {
                if (cur->left) {
                    st.push(cur->left);
                } else {
                    goleft = false;
                }
            } else {
                st.pop();
                result.push_back(cur->val);
                if (cur->right) {
                    st.push(cur->right);
                    goleft = true;
                }
            }
        }
        return result;
    }
};
} // namespace v2

namespace v3 {
/*
用 stack 来模拟 v1 中的递归调用, 这种方式可以把任何递归都转换为循环.
但效率上不如 v1 和 v2.
*/
class Solution {
    struct Frame {
        TreeNode* node;
        int ret; // 相当于函数返回地址
    };

public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<Frame> st;
        st.push(Frame{root, -1});
        int pc = 0; // 指向下一指令地址, 相当于指令寄存器
        while (!st.empty()) {
            switch (pc) {
            case 0: {
                if (!st.top().node) {
                    pc = st.top().ret;
                    st.pop();
                } else {
                    st.push(Frame{st.top().node->left, 1});
                    pc = 0;
                }
            } break;
            case 1: {
                result.push_back(st.top().node->val);
                st.push(Frame{st.top().node->right, 2});
                pc = 0;
            } break;
            case 2: {
                pc = st.top().ret;
                st.pop();
            } break;
            }
        }
        return result;
    }
};
} // namespace v3

USING_MAKE_BINARY_TREE;

TEST_CASE("Binary Tree Inorder Traversal") {
    TEST_SOLUTION(inorderTraversal, v1, v2, v3) {
        CHECK(inorderTraversal(makeBT({})) == vector<int>{});
        CHECK(inorderTraversal(makeBT({3, 1, 2})) == vector<int>{1, 3, 2});
        CHECK(inorderTraversal(makeBT({3, 2, 4, 1, 0, 0, 5})) ==
              vector<int>{1, 2, 3, 4, 5});

        auto t = makeBT({3, 2, 4, 1, 0, 0, 5});
        BENCHMARK("") { return inorderTraversal(t); };
        freeTree(t);
    };
}

} // namespace binary_tree_inorder_traversal
