#include <vector>

/*
    Leetcode 62 Unique Paths
    There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]).
    The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either
    down or right at any point in time.

    Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

    The test cases are generated so that the answer will be less than or equal to 2 * 109.

    Algorithm;
    2 D Dynamic Programming problem.
    Create 2-D dp matrix.
    Last row and last column will have only one way of reaching goal.
    For all other cells, the number of ways are: num way in right cell + num ways in down cell.
*/
using namespace std;
class Solution {
public:
    /**
     * @brief Given the two integers m and n, return the number of possible unique paths that
     * the robot can take to reach the bottom-right corner.
     * @param m Int number of rows.
     * @param n Int number of cols.
     * @returns Int number of ways to go from start to goal position.
     */
    int uniquePaths(int m, int n) {
       // DP matrix to store the number of way to reach goal from a point.
       std::vector<std::vector<int>> dp_matrix(m, std::vector<int>(n, 0));

       // Base cases at the edges.
       for (auto & row : dp_matrix) {
            row[n - 1] = 1;
       }

       for (auto & col : dp_matrix[m - 1]) {
            col = 1;
       }

       for (int i = m - 2; i>=0; i--) {
        for (int j = n - 2; j>=0; j--) {
            dp_matrix[i][j] = dp_matrix[i + 1][j] + dp_matrix[i][j + 1];
        }
       }
       return dp_matrix[0][0];
    }
};