/*
Unique Paths II

URL: https://leetcode.com/problems/unique-paths-ii
Tags: ['array', 'dynamic-programming']
___

A robot is located at the top-left corner of a m x n grid (marked  'Start' in
the diagram below).

The robot can only move either down or right at any point in time. The robot
is trying to reach the bottom-right corner of the grid (marked 'Finish' in the
diagram below).

Now consider if some obstacles are added to the grids. How many unique paths
would there be?

![](https://assets.leetcode.com/uploads/2018/10/22/robot_maze.png)

An obstacle and empty space is marked as `1` and `0` respectively in the grid.

Note: m and n will be at most 100.

Example 1:

    Input: [
      [0,0,0],
      [0,1,0],
      [0,0,0]
    ]
    Output: 2
    Explanation:
    There is one obstacle in the middle of the 3x3 grid above.
    There are two ways to reach the bottom-right corner:
    1. Right - > Right -> Down -> Down
    2. Down -> Down -> Right -> Right
*/

#include <vector>
#include "catch.hpp"

using std::vector;

namespace unique_paths_ii {

inline namespace v1 {
// 延续 062 unique paths 中 v3 动态规划的思路
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid.front().size();
        vector<std::vector<int>> dp(m, vector<int>(n));
        for (auto i = 0; i < m; i++) {
            for (auto j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    if (i == 0 && j == 0) {
                        dp[i][j] = 1;
                    } else {
                        auto a = i < 1 ? 0 : dp[i - 1][j];
                        auto b = j < 1 ? 0 : dp[i][j - 1];
                        dp[i][j] = a + b;
                    }
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
} // namespace v1

TEST_CASE("Unique Paths II") {
    Solution s;

    auto v = vector<vector<int>>{
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
    };
    CHECK(s.uniquePathsWithObstacles(v) == 2);

    v = vector<vector<int>>{{1}};
    CHECK(s.uniquePathsWithObstacles(v) == 0);
}

} // namespace unique_paths_ii
