
/*
Minimum Path Sum

URL: https://leetcode.com/problems/minimum-path-sum
Tags: ['array', 'dynamic-programming']
___

Given a m x n grid filled with non-negative numbers, find a path from top left
to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

    Input:
    [
      [1,3,1],
      [1,5,1],
      [4,2,1]
    ]
    Output: 7
    Explanation: Because the path 1 ->3->1->1->1 minimizes the sum.
*/

#include "test.h"

using std::numeric_limits;
using std::vector;

namespace minimum_path_sum {

/*
    Time Limit Exceeded
*/
inline namespace v1 {
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        return step(grid, grid.size() - 1, grid.front().size() - 1);
    }

private:
    int step(vector<vector<int>>& grid, int m, int n) {
        if (m == 0 && n == 0) {
            return grid[0][0];
        }
        int up = numeric_limits<int>::max(), left = numeric_limits<int>::max();
        if (m > 0) {
            up = step(grid, m - 1, n);
        }
        if (n > 0) {
            left = step(grid, m, n - 1);
        }
        return (up < left ? up : left) + grid[m][n];
    }
};
} // namespace v1

/*
    主要思路还是 v1 的, 但缓存了每次计算的结果
*/
namespace v2 {

using std::min;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<int> record(grid.front().size() + 1, numeric_limits<int>::max());
        record[1] = 0; // 这样就避免了对 grid[0][0] 这个节点的特殊处理了
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.front().size(); j++) {
                record[j + 1] = min(record[j], record[j + 1]) + grid[i][j];
            }
        }
        return record.back();
    }
};
} // namespace v2

TEST_CASE("Minimum Path Sum") {
    TEST_SOLUTION(minPathSum, v1) {
        vector<vector<int>> m = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
        CHECK(minPathSum(m) == 7);
    };
}

} // namespace minimum_path_sum
