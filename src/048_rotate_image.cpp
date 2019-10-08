
/*
Rotate Image

URL: https://leetcode.com/problems/rotate-image
Tags: ['array']
___

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image [in-place](https://en.wikipedia.org/wiki/In-
place_algorithm), which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.

Example 1:

    Given input matrix =
    [
      [1,2,3],
      [4,5,6],
      [7,8,9]
    ],

    rotate the input matrix in-place such that it becomes:
    [
      [7,4,1],
      [8,5,2],
      [9,6,3]
    ]


Example 2:

    Given input matrix =
    [
      [ 5, 1, 9,11],
      [ 2, 4, 8,10],
      [13, 3, 6, 7],
      [15,14,12,16]
    ],

    rotate the input matrix in-place such that it becomes:
    [
      [15,13, 2, 5],
      [14, 3, 4, 1],
      [12, 6, 8, 9],
      [16, 7,10,11]
    ]
*/

#include "test.h"

using std::swap;
using std::vector;

namespace rotate_image {

inline namespace v1 {
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for (int i = 0, offset = matrix.size() - 1; offset > 0;
             i++, offset -= 2) {
            for (int j = 0; j < offset; j++) {
                swap(matrix[i][i + j], matrix[i + j][i + offset]);
                swap(matrix[i][i + j], matrix[i + offset][i + offset - j]);
                swap(matrix[i][i + j], matrix[i + offset - j][i]);
            }
        }
    }
};
} // namespace v1

TEST_CASE("Rotate Image") {
    TEST_SOLUTION(rotate, v1) {
        vector<vector<int>> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        rotate(v);
        CHECK(v == vector<vector<int>>{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
    };
}

} // namespace rotate_image
