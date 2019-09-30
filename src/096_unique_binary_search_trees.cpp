/*
Unique Binary Search Trees

URL: https://leetcode.com/problems/unique-binary-search-trees
Tags: ['dynamic-programming', 'tree']
___

Given n , how many structurally unique BST 's (binary search trees) that store
values 1 ...  n?

Example:

    Input: 3
    Output: 5
    Explanation: Given n = 3, there are a total of 5 unique BST 's:

       1         3     3      2      1
        \       /     /      / \      \
         3     2     1      1   3      2
        /     /       \                 \
       2     1         2                 3
*/

#include "test.h"

using std::map;
using std::vector;

namespace unique_binary_search_trees {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

inline namespace v1 {
/*
想完全照搬 095 unique binary search trees ii 的思路是不行的, 太慢了.
这题考察的是卡特兰数,其递推形式是:
C(n) = 累加[C(i)*C(n-1-i), i from 0 to n - 1], 且 C(0) = 1.
或者卡兰特数也可以是:
C(n) = f(2n) = 累加[f(i-1)*f(2n-1-i), i from 1 to 2n-1], 且 f(0) = 1.
这个形式就是括号配对问题, 栈进出问题的推导结果.

如何将查找二叉树的问题映射成为栈的进出问题呢?
首先要明白一点就是只要BST的形态是确定的, 那每个节点上填入的数字也是确定的
(可以想象将 BST 压扁成一个数组)
所以这题本质上是在问, 由 n 个节点组成的二叉树有多少种可能的形态.
首先将这棵二叉树补满成为一棵满二叉树,
这时我们就一共有(2n+1)个可用的节点(其中一个是根节点).
接下去的逻辑就变成, 从根节点出发, 可以画出多少种不同的**满二叉树**.
记往左一步等价于入栈, 往右一步等价于出栈,
则该问题转换成为了栈进出(或括号匹配)问题了, 可以套上面第二个的公式了.
*/
class Solution {
public:
    int numTrees(int n) {
        map<int, int> record;
        return step(n, record);
    }

private:
    // 套用上面第一个递推公式,
    // record 记录已经计算过的结果, 避免重复计算.
    int step(int n, map<int, int>& record) {
        if (n == 0) {
            return 1;
        }
        auto iter = record.find(n);
        if (iter != record.end()) {
            return iter->second;
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            result += step(i, record) * step(n - 1 - i, record);
        }
        record[n] = result;
        return result;
    }
};
} // namespace v1

TEST_CASE("Unique Binary Search Trees") {
    TEST_SOLUTION(numTrees, v1) {
        CHECK(numTrees(3) == 5);
        CHECK(numTrees(19) == 1767263190);

        BENCHMARK("") { return numTrees(19); };
    };
}

} // namespace unique_binary_search_trees
