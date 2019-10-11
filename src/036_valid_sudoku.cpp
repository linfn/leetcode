
/*
Valid Sudoku

URL: https://leetcode.com/problems/valid-sudoku
Tags: ['hash-table']
___

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be
validated  according to the following rules :

  1. Each row must contain the digits `1-9` without repetition.
  2. Each column must contain the digits `1-9` without repetition.
  3. Each of the 9 `3x3` sub-boxes of the grid must contain the digits `1-9`
without repetition.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-
by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)
A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with
the character `'.'`.

Example 1:

    Input:
    [
      [ "5","3",".",".","7",".",".",".","."],
      ["6",".",".","1","9","5",".",".","."],
      [".","9","8",".",".",".",".","6","."],
      ["8",".",".",".","6",".",".",".","3"],
      ["4",".",".","8",".","3",".",".","1"],
      ["7",".",".",".","2",".",".",".","6"],
      [".","6",".",".",".",".","2","8","."],
      [".",".",".","4","1","9",".",".","5"],
      [".",".",".",".","8",".",".","7","9"]
    ]
    Output: true


Example 2:

    Input:
    [
       ["8","3",".",".","7",".",".",".","."],
      ["6",".",".","1","9","5",".",".","."],
      [".","9","8",".",".",".",".","6","."],
      ["8",".",".",".","6",".",".",".","3"],
      ["4",".",".","8",".","3",".",".","1"],
      ["7",".",".",".","2",".",".",".","6"],
      [".","6",".",".",".",".","2","8","."],
      [".",".",".","4","1","9",".",".","5"],
      [".",".",".",".","8",".",".","7","9"]
    ]
    Output: false
    Explanation: Same as Example 1, except with the 5 in the top left corner
being modified to 8. Since there are two 8 's in the top left 3x3 sub-box, it is
invalid.


Note:

  * A Sudoku board (partially filled) could be valid but is not necessarily
solvable.
  * Only the filled cells need to be validated according to the mentioned rules.
  * The given board contain only digits `1-9` and the character `'.'`.
  * The given board size is always `9x9`.
*/

#include "test.h"

using std::vector;

namespace valid_sudoku {

inline namespace v1 {
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool bitmaps[3][9];
        auto checkDup = [&](int k, int i, int j) {
            int n = board[i][j] - '1';
            if (n < 0 || n >= 9) {
                return false;
            }
            if (bitmaps[k][n]) {
                return true;
            }
            bitmaps[k][n] = true;
            return false;
        };
        for (int i = 0; i < 9; i++) {
            for (int k = 0; k < 3; k++) {
                memset(&bitmaps[k][0], 0, sizeof(bitmaps[k]));
            }
            for (int j = 0; j < 9; j++) {
                if (checkDup(0, i, j) || checkDup(1, j, i) ||
                    checkDup(2, (i / 3) * 3 + (j / 3), (i % 3) * 3 + (j % 3))) {
                    return false;
                }
            }
        }
        return true;
    }
};
} // namespace v1

TEST_CASE("Valid Sudoku") {
    TEST_SOLUTION(isValidSudoku, v1) {
        vector<vector<char>> v = {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
        CHECK(isValidSudoku(v));
        v[0][0] = '3';
        CHECK_FALSE(isValidSudoku(v));
    };
}

} // namespace valid_sudoku
