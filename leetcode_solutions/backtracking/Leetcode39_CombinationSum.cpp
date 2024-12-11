#include <vector>
/*
    Leetcode 39 Combination Sum
    Given an array of distinct integers candidates and a target integer target, return a list of all unique
    combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

    The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the
    frequency of at least one of the chosen numbers is different.

    The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations
    for the given input.

    Algorithm:
    Depth first search(i, curr_comb, current sum, candidates)

        if (index >= length or current sum > target) {
            return;
        }

        if (sum == target) {
            add combination to result.
            return.
        }

        create copies of current comb and current sum for below cases.

        // Add index i again to combination.
        current_sum1 += ith
        current_comb1.add(ith)

        // Do NOT add anything to the combination.
        current comb .pop back
        current sum -= ith
        dfs(i + 1, curr_comb, current_sum, candidates)

    If you are passing current combination by reference, then the pop_back() action is needed to correct the combination
    for the next case where you are NOT adding any number to the combination..

    if not passing by reference (passing by value), you can do the non-addition step first and then the addition of new
    element step. However, this is extremely inefficient.

    Thus, passing by reference and passing by value result in algorithmic changes with significant efficiency effects.
*/

class Solution {
public:
    /**
     * @brief Gives a list of all unique combinations of candidates where the chosen numbers sum to target.
     * Calls depth first search internally.
     * @param candidates Vector of ints of input numbers.
     * @param target Integer target to which the sum should match for all combinations.
     * @returns Vector of vector of ints containing all the combinations.
     */
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        // Initialization.
        std::vector<int> current_combination;
        int current_sum = 0;
        std::vector<std::vector<int>> result;

        // DFS on first index of input.
        depth_first_search(candidates, 0, current_sum, current_combination, target, result);
        return result;
    }

private:
    /**
     * @brief Depth First Search with backtracking to query all possible combinations summing up to target.
     * @param candidates Vector of ints of input numbers.
     * @param index Integer index of input array on which DFS is applied.
     * @param current_sum Integer sum of the current combination.
     * @param target Integer target.
     * @param [out] result Vector of int vectors containing all possible combinations.
     */
    void depth_first_search(
        std::vector<int>& candidates,
        int index,
        int current_sum,
        std::vector<int> & current_combination,
        int target,
        std::vector<std::vector<int>> &result) {

        // Target sum found.
        if (current_sum == target) {
            result.emplace_back(current_combination);
            return;
        }

        // Input exhausted, or target exceeded.
        if(index >= candidates.size() || current_sum > target) {
            return;
        }

        // Add the index i to the combination.
        current_sum += candidates[index];
        current_combination.emplace_back(candidates[index]);
        depth_first_search(
            candidates,
            index,
            current_sum,
            current_combination,
            target,
            result);

        // Do not add number to the combination and add the next one.
        current_combination.pop_back();
        current_sum -= candidates[index];
        depth_first_search(
            candidates,
            index + 1,
            current_sum,
            current_combination,
            target,
            result);
    }
};

// SIGNIFICANTLY LESS OPTIMAL SOLUTION: Very little difference though.
// class Solution {
// public:
//     std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
//         std::vector<int> current_combination;
//         int current_sum = 0;
//         std::vector<std::vector<int>> result;

//         depth_first_search(candidates, 0, current_sum, current_combination, target, result);
//         return result;
//     }

// private:
//     void depth_first_search(
//         std::vector<int>& candidates,
//         int index,
//         int current_sum,
//         std::vector<int> current_combination,
//         int target,
//         std::vector<std::vector<int>> &result) {

//         // Target sum found.
//         if (current_sum == target) {
//             result.emplace_back(current_combination);
//             return;
//         }

//         // Input exhausted, or target exceeded.
//         if(index >= candidates.size() || current_sum > target) {
//             return;
//         }

//         // Do not add number to the combination.
//         depth_first_search(
//             candidates,
//             index + 1,
//             current_sum,
//             current_combination,
//             target,
//             result);

//         // Add the index i again to the combination.
//         current_sum += candidates[index];
//         current_combination.emplace_back(candidates[index]);
//         depth_first_search(
//             candidates,
//             index,
//             current_sum,
//             current_combination,
//             target,
//             result);

//     }
// };