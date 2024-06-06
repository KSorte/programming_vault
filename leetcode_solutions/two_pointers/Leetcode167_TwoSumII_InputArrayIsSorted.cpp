#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Given a 1-indexed array of integers numbers that is already sorted
 * in non-decreasing order, find two numbers such that they add up to a specific
 * target number. Let these two numbers be numbers[index1] and numbers[index2]
 * where 1 <= index1 < index2 <= numbers.length.
 *
 * Return the indices of the two numbers, index1 and index2, added by one as an
 * integer array [index1, index2] of length 2.
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 * Your solution must use only constant extra space.
 *
 * The solution to this also relies on a two pointer approach with iterators starting
 * from the opposite ends of the array.
 *
 * Steps:
 * 1. Initialize two iterators i and j from left and right of the array respectively.
 * 2. Start a while loop with condition (i < j) -> not i <= j because an element can't be used twice.
 *  a. if sum(ith and jth element) < target => i++
 *  b. else if sum(ith and jth element) > target => j--
 *  c. else when sum(ith and jth element) == target => return [i + 1, j + 1]
 * 3. if we come out of while loop, return an empty array.
 *
 * @param numbers Array of numbers as input.
 * @param target Target sum.
 * @returns Vector of indices that add up to the sum.
 */

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {

        // Initialize vector that would contain the indices of the two integers.
        std::vector<int> indices(2);

        // Initialize iterators.
        int i = 0, j = numbers.size() - 1;

        while (i < j){
            // If sum smaller than target, increment left number.
            if (numbers[i] + numbers[j] < target){
                i++;
            } else if(numbers[i] + numbers[j] > target){
            // If sum larger than target, decrement right number.
                j--;
            } else {
            // If sum equals the target, return the indices.
                indices[0] = i + 1;
                indices[1] = j + 1;
                return indices;
            }
        }
    return indices;
    }
};

int main() {
    // Test cases
    std::vector<std::vector<int>> testCases = {
        {2, 7, 11, 15},  // Test case 1
        {2, 3, 4},       // Test case 2
        {-1, 0},         // Test case 3
        {0, 0, 3, 4},    // Test case 4
        {-5, -4, -3, -2, -1, 0, 3, 4, 5, 6}  // Test case 5
    };

    // Corresponding targets for each test case
    std::vector<int> targets = {9, 6, -1, 0, 0};

    // Create an instance of the Solution class
    Solution solution;

    // Iterate over test cases
    for (int i = 0; i < testCases.size(); ++i) {
        std::vector<int> indices = solution.twoSum(testCases[i], targets[i]);
        std::cout << "Test Case " << (i + 1) << ": ";
        if (!indices.empty()) {
            std::cout << "[" << indices[0] << ", " << indices[1] << "]";
        } else {
            std::cout << "No solution found.";
        }
        std::cout << std::endl;
    }

    return 0;
}