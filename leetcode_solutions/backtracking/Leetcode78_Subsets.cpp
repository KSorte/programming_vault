#include <vector>
/*
    Leetcode 78 Subsets
    Given an integer array nums of unique elements, return all possible
    subsets
    (the power set).

    The solution set must not contain duplicate subsets. Return the solution in any order.

    Algorithm:
    Do a depth first search for solutions.

    void DFS Function(i, &nums, &S(list of subsets), s(current subset)) :
        if (i >= length) {
        return
        }
        // Do not add ith element to the set.
        DFS(i + 1, S, s)

        // Add ith element to the set.
        s.add(ith element)
        S.add(s)
        DFS(i + 1, S, s)
*/

class Solution {
public:
    /**
     * @brief Return all possible subsets. See description.
     * @param nums Vector of int of which subsets need to be found out.
     * @returns Vector of integer vectors containing all possible subsets.
     */
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<int> current_subset;
        std::vector<std::vector<int>> result;

        // Add empty set to result.
        result.emplace_back(current_subset);

        // Depth first search.
        depth_first_search(0, nums, result, current_subset);

        return result;
    }

private:
    /**
     * @brief Depth First Search for finding all the possible subsets
     * from ith element onwards.
     * @param index Integer index of the nums from where dfs needs to be applied.
     * @param result [out] Vector of integer vectors containing all possible subsets.
     * @param current_subset Integer vector representing current subset being constructed.
     */
    void depth_first_search(
        int index,
        std::vector<int> &nums,
        std::vector<std::vector<int>> &result,
        std::vector<int> current_subset) {

        if (index >= nums.size()) {
            // If reached the end of the nums array.
            return;
        }

        // Do not add ith element to the current subset.
        depth_first_search(index + 1, nums, result, current_subset);

        // Update current subset and result.
        current_subset.emplace_back(nums[index]);
        result.emplace_back(current_subset);
        depth_first_search(index + 1, nums, result, current_subset);
    }
};