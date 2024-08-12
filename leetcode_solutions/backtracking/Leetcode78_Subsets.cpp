#include <vector>
/*
    Leetcode 78 Subsets
    Given an integer array nums of unique elements, return all possible
    subsets
    (the power set).

    The solution set must not contain duplicate subsets. Return the solution in any order.

    Algorithm:
    Do a depth first search for solutions.

    void DFS Function(i, &nums, &S(list of subsets), &s(current subset)) :
        if (i >= length) {
        return
        }

        // Add ith element to the set.
        s.add(ith element)
        S.add(s)
        DFS(i + 1, S, s)

        // Do not add ith element to the set.
        s.pop_back();
        DFS(i + 1, S, s)

    If you are passing current subset by reference, then the pop_back() action is needed to correct the subset
    for the case where you are NOT adding any element to the subset.

    if not passing by reference (passing by value), you can do the non-addition step first and then the addition of new
    element step. However, this is extremely inefficient.

    Thus, passing by reference and passing by value result in algorithmic changes with significant efficiency effects.
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
     * @brief Depth First Search with backtracking for finding all the possible subsets
     * from ith element onwards.
     * @param index Integer index of the nums from where dfs needs to be applied.
     * @param result [out] Vector of integer vectors containing all possible subsets.
     * @param current_subset Integer vector representing current subset being constructed.
     */
    void depth_first_search(
        int index,
        std::vector<int> &nums,
        std::vector<std::vector<int>> &result,
        std::vector<int> &current_subset) {

        if (index >= nums.size()) {
            // If reached the end of the nums array.
            return;
        }

        // Update current subset and result.
        current_subset.emplace_back(nums[index]);
        result.emplace_back(current_subset);
        depth_first_search(index + 1, nums, result, current_subset);

        // Do not add ith element to the current subset.
        current_subset.pop_back();
        depth_first_search(index + 1, nums, result, current_subset);
    }
};

// Slightly different but massively suboptimal.
// class Solution {
// public:
//     std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
//         std::vector<int> current_subset;
//         std::vector<std::vector<int>> result;

//         // Add empty set to result.
//         result.emplace_back(current_subset);

//         // Depth first search.
//         depth_first_search(0, nums, result, current_subset);

//         return result;
//     }

// private:
//     void depth_first_search(
//         int index,
//         std::vector<int> &nums,
//         std::vector<std::vector<int>> &result,
//         std::vector<int> current_subset) {

//         if (index >= nums.size()) {
//             // If reached the end of the nums array.
//             return;
//         }

//         // Do not add ith element to the current subset.
//         depth_first_search(index + 1, nums, result, current_subset);

//         // Update current subset and result.
//         current_subset.emplace_back(nums[index]);
//         result.emplace_back(current_subset);
//         depth_first_search(index + 1, nums, result, current_subset);
//     }
// };