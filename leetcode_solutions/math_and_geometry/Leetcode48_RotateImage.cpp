#include <algorithm>
#include <vector>

/*
    Leetcode 48 Rotate Image.
    You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

    You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
    DO NOT allocate another 2D matrix and do the rotation.

    Approach:
    Play with a 2x2 matrix to notice patterns.
    Two methods emerge.
        - Reverse all vectors and then mirror the matrix about the line
        going from top right to bottom left.
        - OR, take transpose (mirror about the line from top left to bottom right) and
            then reverse all the vectors.
    Second approach is simpler.
*/
class Solution {
public:
    /**
     * @brief Rotate the image matrix 90 clockwise in place.
     * @param matrix std::vector<std::vector<int>> image matrix to be rotated.
     */
    void rotate(std::vector<std::vector<int>>& matrix) {
        // Transpose.
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < row; col ++) {
                // Swap for transposing the matrix.
                std::swap(matrix[row][col], matrix[col][row]);
            }
        }

        // Reverse all row vectors.
        for (auto & row_vector : matrix) {
            std::reverse(row_vector.begin(), row_vector.end());
        }
    }
};