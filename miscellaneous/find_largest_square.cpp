# include <algorithm>
# include <cmath>
# include <iostream>
# include <vector>
/*
 * Problem: Find the Largest Square Sub-Matrix of Ones
 *
 * Description:
 * Implement a function `int find_largest_square(vector<vector<int>> matrix)`
 * that searches within a given 2D binary matrix (composed of 0s and 1s)
 * to find the size of the largest square sub-matrix consisting only of ones (1s).
 *
 * Input:
 * - A 2D vector `matrix` of integers (0s and 1s).
 *
 * Output:
 * - An integer representing the size (length of one side) of the largest square
 *   sub-matrix of ones found within the given matrix.
 *
 * Example:
 * Input Matrix:
 * 1 1 0 1 0
 * 1 1 1 1 1
 * 0 0 1 1 1
 * 1 0 1 1 1
 * 1 0 0 0 0
 *
 * Expected Output:
 * 3 (The largest square matrix of ones is 3x3)
 *
 * Constraints:
 * - The matrix may have varying dimensions.
 * - Efficient algorithms (e.g., dynamic programming) are encouraged for large inputs.
 */

class Solution {
public:
    /**
     * @brief Find the area of the largest square of 1's using 2D dynamic programming.
     *
     * @param matrix Vector of vector of char
     * @return int Max size of the required square.
     */
    int maximalSquare(std::vector<std::vector<char>>& matrix) {
        // Dimensions of the matrix
        size_t num_rows = matrix.size();
        size_t num_cols = matrix[0].size();

        // Initialize dp matrix to 0.
        std::vector<std::vector<int>> dp_matrix (num_rows, std::vector<int>(num_cols, 0));

        // Max size
        int max_size = 0;

        // Base condition for the first row
        for (int i = 0; i < num_cols; i++) {
            dp_matrix[0][i] = matrix[0][i] - '0';
            max_size = std::max(max_size, dp_matrix[0][i]);
        }

        // Base condition for the first column.
        for (int i = 0; i < num_rows; i++) {
            dp_matrix[i][0] = matrix[i][0] - '0';
            max_size = std::max(max_size, dp_matrix[i][0]);
        }

        for (int i = 1; i < num_rows; i++) {
            for (int j = 1; j < num_cols; j++) {
                int value = matrix[i][j] - '0';
                if (value == 1) {
                    // Check neighbors if 1.
                    dp_matrix[i][j] += std::min({
                        dp_matrix[i-1][j],
                        dp_matrix[i-1][j-1],
                        dp_matrix[i][j-1]}) + 1;
                    // Update max size.
                    max_size = std::max(max_size, dp_matrix[i][j]);
                }
            }
        }
        return pow(max_size, 2);
    }
};

int main() {
    Solution sol;

    // Test Case 1
    std::vector<std::vector<char>> matrix1 = {
        {'1', '1', '0', '1', '0'},
        {'1', '1', '1', '1', '1'},
        {'0', '0', '1', '1', '1'},
        {'1', '0', '1', '1', '1'},
        {'1', '0', '0', '0', '0'}
    };
    std::cout << "Test Case 1: " << sol.maximalSquare(matrix1) << std::endl;

    // Test Case 2
    std::vector<std::vector<char>> matrix2 = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    std::cout << "Test Case 2: " << sol.maximalSquare(matrix2) << std::endl;

    // Test Case 3: Single row
    std::vector<std::vector<char>> matrix3 = {
        {'1', '1', '1', '1', '1'}
    };
    std::cout << "Test Case 3: " << sol.maximalSquare(matrix3) << std::endl;

    // Test Case 4: Single column
    std::vector<std::vector<char>> matrix4 = {
        {'1'},
        {'1'},
        {'1'},
        {'1'}
    };
    std::cout << "Test Case 4: " << sol.maximalSquare(matrix4) << std::endl;

    // Test Case 5: No 1s
    std::vector<std::vector<char>> matrix5 = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    std::cout << "Test Case 5: " << sol.maximalSquare(matrix5) << std::endl;

    return 0;
}