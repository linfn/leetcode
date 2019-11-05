
/*
Path Sum III

URL: https://leetcode.com/problems/path-sum-iii
Tags: ['tree']
___

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go
downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range
-1,000,000 to 1,000,000.

Example:

    root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

          10
         /  \
        5   -3
       / \    \
      3   2   11
     / \   \
    3  -2   1

    Return 3. The paths that sum to 8 are:

    1.  5 -> 3
    2.  5 -> 2 -> 1
    3. -3 -> 11
*/

#include "test.h"

using namespace leetcode;

namespace path_sum_iii {

inline namespace v1 {
class Solution {
public:
public:
    int pathSum(TreeNode* root, int sum) {
        if (!root) {
            return 0;
        }
        return step(root, sum) + pathSum(root->left, sum) +
               pathSum(root->right, sum);
    }

private:
    int step(TreeNode* root, int sum) {
        int result = 0;
        if (!root) {
            return result;
        }
        if (root->val == sum) {
            result++;
        }
        result += step(root->left, sum - root->val) +
                  step(root->right, sum - root->val);
        return result;
    }
};
} // namespace v1

TEST_CASE("Path Sum III") {
    TEST_SOLUTION(pathSum, v1) {
        CHECK(pathSum(makeTree({10, 5, -3, 3, 2, 0, 11, 3, -2, 0, 1}), 8) == 3);
    };
}

} // namespace path_sum_iii
