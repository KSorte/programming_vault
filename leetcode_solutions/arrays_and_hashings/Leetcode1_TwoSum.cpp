#include<iostream>
#include<vector>
#include <algorithm>

/**
 * @brief Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Steps for brute force method: O(n^2)
 * 1. This solutions consists of two for loops.
 * 2. One for loop queries for index of first number (i), and the second for loop(j) iterates over all indices
 * ahead of i.
 * 3. If nums[i] + nums[j] is target, then return a vector of nums[i] and nums[j].
 *
 * Steps for the solution using an unordered map: Most efficient
 * 1. Initialize an unordered map mapping from value to index.
 *  Unordered map is preferred because the map.find() operation has a time complexity of O(1) on average.
 * 2. Iterate through the array using i and compute complement of each
 * number as target - number
 *      a. If the complement exists in the map (using map.find), return complement index and i.
 *      b. If the complement doesn't exist, add the current number and its index to the map.
 * 3. Return empty output by default.
 *
 * @param nums Vector of integers
 * @param target Target sum
 * @returns A vector of 2 integers summing up to the target.
 */
class Solution {
public:
    // Searching for the right combination using brute force.
    std::vector<int> twoSum_BruteForce(std::vector<int>& nums, int target) {
    std::vector<int> output;
    for(int i = 0; i<nums.size();i++)
    {
        for (int j = i+1;j<nums.size();j++)
        {
            if (nums[i]+nums[j]==target)
            {
                output.push_back(i);
                output.push_back(j);
                return output;
            }
        }
    }
    return output;
    }

    // Time Complexity: O(n)
    // For loop is O(n) and the map.find is on average O(1).
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // Initialize vector to store output.
        std::vector<int> output;

        // Map to store value-index association.
        std::unordered_map<int, int> map;

        for (int i = 0; i < nums.size(); i++){
            // Compute complement to the current number
            auto complement = target - nums[i];
            // If complement exists in the map, return the pair.
            if (map.find(complement) != map.end()){
                output.emplace_back(map[complement]);
                output.emplace_back(i);
                return output;
            }

            // Else, add the new value-index pair to the map.
            map.insert({nums[i], i});
        }
        return output;
    }

    /**
     * This approach doesn't handle the edge case if the two numbers are duplicates.
     * This is because std::find only finds the first occurance of the element in the original array.
     * For example this algo fails on [3,3]. There are workarounds, but I feel it is not worth it to explore
     * the two pointer approach for this problem.
    */
    // Using two pointer approach.
    std::vector<int> twoSum_two_pointer(std::vector<int>& nums, int target) {
        // Initialize vector to store output.
        std::vector<int> output;
        // Initialize vector to store the sorted input vector nums.
        std::vector<int> nums_sorted = nums;
        // Sort the vector in ascending order.
        std::sort(nums_sorted.begin(), nums_sorted.end());
        int i = 0, j = nums_sorted.size() - 1;

        while (i < j){
            if (nums_sorted[i] + nums_sorted[j] < target){
                i++;
            } else if(nums_sorted[i] + nums_sorted[j] > target){
                j--;
            } else {
                // If sum equals target, find the elememt in the original vector.
                auto it_i = std::find(nums.begin(), nums.end(), nums_sorted[i]);
                auto it_j = std::find(nums.begin(), nums.end(), nums_sorted[j]);
                // Index is the distance of the iterator it_i from the beginning.
                output.emplace_back(std::distance(nums.begin(), it_i));
                // Index is the distance of the iterator it_j from the beginning.
                output.emplace_back(std::distance(nums.begin(), it_j));
                return output;
            }
        }
        return output;
    }
};

int main() {
    Solution solution;
    // Test case
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    std::vector<int> result1 = solution.twoSum(nums1, target1);
    std::cout << "Test Case 1:" << std::endl;
    std::cout << "Input: nums = {2, 7, 11, 15}, target = 9" << std::endl;
    std::cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << std::endl << std::endl;
    return 0;
}