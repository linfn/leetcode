/*
Unique Paths

URL: https://leetcode.com/problems/unique-paths
Tags: ['array', 'dynamic-programming']
___

A robot is located at the top-left corner of a m x n grid (marked  'Start' in
the diagram below).

The robot can only move either down or right at any point in time. The robot
is trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

How many possible unique paths are there?

![](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)
Above is a 7 x 3 grid. How many possible unique paths are there?

Note: m and n will be at most 100.

Example 1:

    Input: m = 3, n = 2
    Output: 3
    Explanation:
    From the top-left corner, there are a total of 3 ways to reach the
bottom-right corner:
    1. Right - > Right -> Down
    2. Right -> Down -> Right
    3. Down -> Right -> Right


Example 2:

    Input: m = 7, n = 3
    Output: 28
*/

#include <map>
#include <tuple>
#include <vector>
#include "catch.hpp"

namespace unique_paths {

namespace v1 {
// 该方案Time Limit Exceeded
// 组合递推式: C(n,k) = C(n-1,k-1) + C(n-1,k)
class Solution {
public:
    int uniquePaths(int m, int n) { return c(m + n - 2, n - 1); }

private:
    int c(int n, int k) {
        if (n == k || k == 0) {
            return 1;
        }
        return c(n - 1, k - 1) + c(n - 1, k);
    }
};
} // namespace v1

namespace v2 {
// 延续 v1 思路, 避免重复计算.
class Solution {
public:
    int uniquePaths(int m, int n) {
        Record r;
        return c(r, m + n - 2, n - 1);
    }

private:
    typedef std::map<std::tuple<int, int>, int> Record;
    int c(Record& record, int n, int k) {
        if (n == k || k == 0) {
            return 1;
        }
        auto iter = record.find(std::make_tuple(n, k));
        if (iter != record.end()) {
            return iter->second;
        }
        auto z = c(record, n - 1, k - 1) + c(record, n - 1, k);
        record[std::make_tuple(n, k)] = z;
        record[std::make_tuple(n, n - k)] = z;
        return z;
    }
};
} // namespace v2

namespace v3 {
// 动态规划
// 设 dp[i,j] 是到达点 (i,j) 方案总共的可能数,
// 则 dp[i,j] = dp[i-1,j]+dp[i,j-1]
// 且 dp[0,j] = 1, dp[i,0] = 1
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
        for (auto i = 1; i < m; i++) {
            for (auto j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
} // namespace v3

inline namespace v4 {
// 在 v3 的基础上优化, 只用一维数组就可以了.
// 另外, 由于此题等价于组合计数(v1版本), 说明也可以用动态规划的方式来求组合计数
// 即 C(n,k) = uniquePaths(n-k,k)
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<int> dp(n, 1);
        for (auto i = 1; i < m; i++) {     // 逐行
            for (auto j = 1; j < n; j++) { // 逐列
                dp[j] = dp[j] + dp[j - 1]; // 和 v3 中等价
            }
        }
        return dp[n - 1];
    }
};
} // namespace v4

TEST_CASE("Unique Paths") {
    Solution s;
    CHECK(s.uniquePaths(3, 2) == 3);
    CHECK(s.uniquePaths(7, 3) == 28);
    CHECK(s.uniquePaths(51, 9) == 1916797311);
}

} // namespace unique_paths
