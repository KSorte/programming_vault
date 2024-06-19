#include <iostream>
#include <vector>

/*
    Leetcode 74 Search 2D Matrix
    You are given an m x n integer matrix matrix with the following two properties:
    Each row is sorted in non-decreasing order.
    The first integer of each row is greater than the last integer of the previous row.
    Given an integer target, return true if target is in matrix or false otherwise.
    You must write a solution in O(log(m * n)) time complexity.

    Binary search to find the right row to search - O(logm)
    Binary search to find the right column to in the row found earlier - O(logn)
*/

class Solution {
public:

    /**
     * @brief Find whether a target exists in the matrix given
     * @param matrix matrix to search, is a vector of vectors
     * @param target integer target to find.
     * @returns Boolean indicating whether the target exists in the matrix.
     */
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        int num_rows = matrix.size();
        // Initialize start and end.
        int start_row = 0, end_row = num_rows - 1, target_row = -1;
        // Return false if target outside matrix range.
        if (target < matrix[start_row][0] || target > matrix[end_row].back()){
            return false;
        }

        // O(log(m)) loop; find the correcr row.
        while (start_row <= end_row) {
            int middle = (end_row + start_row)/2;
                std::cout<<middle<<std::endl;

            // If middle is target, return it.
            if (target <= matrix[middle].back() && target >= matrix[middle][0]) {
                // target inside middle row.
                target_row = middle;
                break;
            }

            // If target greater than middle, go right.
            if (target > matrix[middle][0]) {
                start_row = middle + 1;
                continue;
            }

            // If target smaller than middle, go left.
            if (target < matrix[middle][0]) {
                end_row = middle - 1;
                continue;
            }
        }

        // If no target row found, return false.
        if(target_row == -1) {return false;}
        // Get row size.
        int num_cols = matrix[target_row].size();
        // Initialize start and end column index.
        int start_col = 0, end_col = num_cols - 1;

        bool result = false;

        // O(log(n)) loop
        while (start_col <= end_col) {
            // If start_col exceed end_cols, return -1 (failure).
            if (start_col > end_col) {
                result = false;
                break;
            }

            int middle = (end_col + start_col)/2;
            // If middle is target, return it.
            if (target == matrix[target_row][middle]) {
                result = true;
                break;
            }

            // If target greater than middle, go right.
            if (target > matrix[target_row][middle]) {
                start_col = middle + 1;
                continue;
            }

            // If target smaller than middle, go left.
            if (target < matrix[target_row][middle]) {
                end_col = middle - 1;
                continue;
            }
        }

    return result;

    }
};

int main(){
    Solution sol;
    std::vector<std::vector<int>> testMatrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    int testTarget = 1;
    bool expectedResult = true;

    bool result = sol.searchMatrix(testMatrix, testTarget);
    std::cout << "Test case: ";
    std::cout << "Expected = " << expectedResult << ", ";
    std::cout << "Actual = " << result << " -> ";
    std::cout << (result == expectedResult ? "PASS" : "FAIL") << std::endl;

    return 0;

}