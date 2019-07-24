
/*
Kth Smallest Element in a BST

URL: https://leetcode.com/problems/kth-smallest-element-in-a-bst
Tags: ['binary-search', 'tree']
___

Given a binary search tree, write a function `kthSmallest` to find the k th
smallest element in it.

Note:
You may assume k is always valid, 1  ≤ k ≤ BST's total elements.

Example 1:

    Input: root = [3,1,4,null,2], k = 1
       3
      / \
     1   4
      \
        2
    Output: 1

Example 2:

    Input: root = [5,3,6,2,4,null,null,1], k = 3
           5
          / \
         3   6
        / \
       2   4
      /
     1
    Output: 3


Follow up:
What if the BST is modified (insert/delete operations) often and you need to
find the kth smallest frequently? How would you optimize the kthSmallest
routine?
*/

#include "test.h"

using namespace std;

namespace kth_smallest_element_in_a_bst {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

inline namespace v1 {
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) { return step(root, k); }

private:
    int step(TreeNode* node, int& k) {
        if (node->left) {
            int val = step(node->left, k);
            if (k == 0) {
                return val;
            }
        }
        k--;
        if (k == 0) {
            return node->val;
        }
        if (node->right) {
            int val = step(node->right, k);
            if (k == 0) {
                return val;
            }
        }
        return 0;
    }
};
} // namespace v1

USING_MAKE_BINARY_TREE;

TEST_CASE("Kth Smallest Element in a BST") {
    TEST_SOLUTION(kthSmallest, v1) {
        CHECK(kthSmallest(makeBT({3, 1, 4, 0, 2}), 1) == 1);
        CHECK(kthSmallest(makeBT({5, 3, 6, 2, 4, 0, 0, 1}), 3) == 3);

        auto t = makeBT({5, 3, 6, 2, 4, 0, 0, 1});
        BENCHMARK("") { return kthSmallest(t, 3); };
        freeTree(t);
    };
}

} // namespace kth_smallest_element_in_a_bst
