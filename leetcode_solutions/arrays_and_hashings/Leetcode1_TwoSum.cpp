#include<iostream>
#include<vector>

/**
 * @brief Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Steps:
 * 1. This solutions consists of two for loops.
 * 2. One for loop queries for index of first number (i), and the second for loop(j) iterates over all indices
 * ahead of i.
 * 3. If nums[i] + nums[j] is target, then return a vector of nums[i] and nums[j].
 * @param nums Vector of integers
 * @param target Target sum
 * @returns A vector of 2 integers summing up to the target.
 */
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
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