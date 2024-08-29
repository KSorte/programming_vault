#include <string>
#include <tuple>
#include <vector>
/*
    Leetcode 1143 Longest Common Subsequence.
    https://leetcode.com/problems/longest-common-subsequence/

    Algorithm:
    Create dp array of size n1+1 x n2+1.
    Assign 0 to first row and first column.

    inside the iteration:
        if t1[i -1] == t2[j - 1]:
            dp(i, j) = dp(i-1, j-1) + 1
        else :
            dp(i, j) = max(dp(i-1, j), dp(i, j-1))
            (This step is highly unintuitive and won't strike)
    return dp(n-1, n-1)
*/
class Solution {
public:
    /**
     * @brief Find the longest common subsequence in two strings
     * @param text1 String 1
     * @param text2 String 2
     * @returns Int length of longest common substring.
     */
    int longestCommonSubsequence(std::string text1, std::string text2) {
        // Length of smaller string.
        int n1;

        // Length of bigger string.
        int n2;

        std::string small, big;

        if (text1.size() < text2.size()) {
            std::tie(n1, small) = std::make_pair(text1.size(), text1);
            std::tie(n2, big) = std::make_pair(text2.size(), text2);
        } else {
            std::tie(n1, small) = std::make_pair(text2.size(), text2);
            std::tie(n2, big) = std::make_pair(text1.size(), text1);
        }

        // DP Matrix of size n1 x n2.
        std::vector<std::vector<int>> dp_matrix(n1 + 1, std::vector<int>(n2 + 1, 0));

        // Dynamic Programming
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (small[i-1] == big[j-1]) {
                    dp_matrix[i][j] = dp_matrix[i-1][j-1] + 1;
                } else {
                    dp_matrix[i][j] = std::max(dp_matrix[i-1][j], dp_matrix[i][j-1]);
                }
            }
        }

        return dp_matrix[n1][n2];
    }
};