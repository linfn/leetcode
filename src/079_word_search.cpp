
/*
Word Search

URL: https://leetcode.com/problems/word-search
Tags: ['array', 'backtracking']
___

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once.

Example:

    board =
    [
      ['A','B','C','E'],
      ['S','F','C','S'],
      ['A','D','E','E']
    ]

    Given word = " ABCCED ", return true.
    Given word =  " SEE ", return true.
    Given word =  " ABCB ", return false.
*/

#include "test.h"

using std::string;
using std::vector;

namespace word_search {

inline namespace v1 {
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (word.empty()) {
            return true;
        }
        vector<vector<bool>> visited(board.size(),
                                     vector<bool>(board.front().size()));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.front().size(); j++) {
                if (step(board, i, j, word.begin(), word.end(), visited)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool step(vector<vector<char>>& board, int i, int j, string::iterator begin,
              string::iterator end, vector<vector<bool>>& visited) {
        if (visited[i][j]) {
            return false;
        }
        if (*begin != board[i][j]) {
            return false;
        }
        begin++;
        if (begin == end) {
            return true;
        }
        visited[i][j] = true;
        if (i > 0) {
            if (step(board, i - 1, j, begin, end, visited)) {
                return true;
            }
        }
        if (i < board.size() - 1) {
            if (step(board, i + 1, j, begin, end, visited)) {
                return true;
            }
        }
        if (j > 0) {
            if (step(board, i, j - 1, begin, end, visited)) {
                return true;
            }
        }
        if (j < board.front().size() - 1) {
            if (step(board, i, j + 1, begin, end, visited)) {
                return true;
            }
        }
        visited[i][j] = false;
        return false;
    }
};
} // namespace v1

TEST_CASE("Word Search") {
    TEST_SOLUTION(exist, v1) {
        vector<vector<char>> v = {
            {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
        CHECK(exist(v, "ABCCED"));
        CHECK(exist(v, "SEE"));
        CHECK_FALSE(exist(v, "ABCB"));
        v = {{'a'}};
        CHECK(exist(v, "a"));
    };
}

} // namespace word_search
