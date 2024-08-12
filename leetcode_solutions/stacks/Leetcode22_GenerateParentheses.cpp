#include<string>
#include<vector>

/*
    Leetcode 22 Generate Parentheses
    Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
*/

class Solution {
public:
    /**
     * @brief Generate all combinations of well-formed parentheses.
     * @param n Int number of parentheses pairs.
     * @returns Vector of string containing all possible combinations.
     */
    std::vector<std::string> generateParenthesis(int n) {
        std::string current_combination;
        std::vector<std::string> result;
        depth_first_search(n, 0, 0, current_combination, result);
        return result;

    }

private:
    /**
     * @brief DFS with backtracking to query all possible parentheses combinations.
     * @param n Int number of parentheses pairs.
     * @param num_open Int number of open braces.
     * @param num_closed Int number of closed braces.
     * @param current_combination Current string combination of parentheses expanded upon.
     * @param [out] result Vector of string containing all possible combinations.
     */
    void depth_first_search(
        int n, int num_open, int num_closed, std::string current_combination,
        std::vector<std::string> &result) {

            if (num_closed > num_open) {
                return;
            }

            // Used all parentheses.
            if (num_open == n && num_closed == n) {
                result.emplace_back(current_combination);
                return;
            }

            // This condition avoids the condition of infinite (
            if (num_open < n) {
                num_open ++;
                current_combination.push_back('(');
                depth_first_search(n, num_open, num_closed, current_combination, result);
                num_open --;
                current_combination.pop_back();
            }

            if (num_open > num_closed) {
                num_closed ++;
                current_combination.push_back(')');
                depth_first_search(n, num_open, num_closed, current_combination, result);
                num_closed --;
                current_combination.pop_back();
            }

    }
};
