/*
Symmetric Tree

URL: https://leetcode.com/problems/symmetric-tree
Tags: ['tree', 'depth-first-search', 'breadth-first-search']
___

Given a binary tree, check whether it is a mirror of itself (ie, symmetric
around its center).

For example, this binary tree `[1,2,2,3,4,4,3]` is symmetric:



        1
       / \
      2   2
     / \ / \
    3  4 4  3




But the following `[1,2,2,null,3,null,3]` is not:



        1
       / \
      2   2
       \   \
       3    3




Note:
Bonus points if you could solve it both recursively and iteratively.
*/

#include <stack>
#include "test.h"

using std::stack;

namespace symmetric_tree {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

inline namespace v1 {
class Solution {
public:
    bool isSymmetric(TreeNode* root) { return check(root, root); }

private:
    bool check(TreeNode* lhs, TreeNode* rhs) {
        if (!lhs || !rhs) {
            if (!lhs && !rhs) {
                return true;
            } else {
                return false;
            }
        }
        if (lhs->val != rhs->val) {
            return false;
        }
        return check(lhs->left, rhs->right) && check(lhs->right, rhs->left);
    }
};
} // namespace v1

namespace v2 {
// 利用 stack 把 v1 的递归转换掉, 但比 v1 要慢
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        stack<TreeNode*> st;
        st.push(root);
        st.push(root);
        while (!st.empty()) {
            auto lhs = st.top();
            st.pop();
            auto rhs = st.top();
            st.pop();
            if (!lhs || !rhs) {
                if (!lhs && !rhs) {
                    continue;
                }
                return false;
            }
            if (lhs->val != rhs->val) {
                return false;
            }
            st.push(rhs->right);
            st.push(lhs->left);
            st.push(rhs->left);
            st.push(lhs->right);
        }
        return true;
    }
};
} // namespace v2

USING_MAKE_BINARY_TREE;

TEST_CASE("Symmetric Tree") {
    TEST_SOLUTION(isSymmetric, v1, v2) {
        CHECK(isSymmetric(makeBT({1, 2, 2, 3, 4, 4, 3})));
        CHECK(!isSymmetric(makeBT({1, 2, 2, 0, 3, 0, 3})));

        auto t = makeBT({1, 2, 2, 3, 4, 4, 3});
        BENCHMARK("") { return isSymmetric(t); };
    };
}

} // namespace symmetric_tree
