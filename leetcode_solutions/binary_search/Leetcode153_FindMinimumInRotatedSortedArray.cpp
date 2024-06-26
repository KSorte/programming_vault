#include <iostream>
#include <vector>
/*
    Leetcode 153 Find Minimum in Rotated Sorted Array

    Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
    For example, the array nums = [0,1,2,4,5,6,7] might become:

    [4,5,6,7,0,1,2] if it was rotated 4 times.
    [0,1,2,4,5,6,7] if it was rotated 7 times.
    Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
    [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

    Given the sorted rotated array nums of unique elements, return the minimum element of this array.

    You must write an algorithm that runs in O(log n) time.

    Algorithm revolves around finding the change over point somehow.
    Use a binary search and determine where the middle point lies in - left sorted array or right.
    If the array is rotated n times, the entire array is basically the left portion.

    First designate the left most as the minimum.
    Steps inside a classic Binary search loop.
    1. Check if L and R are in a sorted portion (L <= R)
        If yes, assign left to min. break;
    2. Calculate middle
        if middle is at a peak -> min =  middle + 1 -> break;
        if middle is at a valley -> min =  middle -> break;
    2. If M is in left portion (M >= L):
        we need to search right. L = M + 1
        continue;
    3. if M is in right portion (M < L)
        We need to search left. R = M - 1

    outside while loop
    return min.
*/

class Solution {
public:

    /**
     * @brief Find minimum in a rotated sorted integer array
     * @param nums Rotated sorted vector of integers
     * @returns Integer minimum in the rotated sorted array
     */
    int findMin(std::vector<int>& nums) {
        // Assign left and right to the ends of the array.
        int left = 0, right = nums.size() - 1;

        // Assign minimum to leftmost at the beginning.
        int min = nums[0];

        while (left <= right) {
            // First check if left and right flank a sorted portion.
            if (nums[left] <= nums[right]){
                min = nums[left];
                break;
            }

            int middle = (left + right) / 2;
            // Check if middle is at a valley or a peak.
            if (middle != 0) {
                // If middle element is greater than the immediate neighborhood.
                if ((nums[middle] > nums[middle - 1]) &&
                    nums[middle] > nums[middle + 1]){
                    min = nums[middle + 1];
                    break;
                }
                // If middle element is smaller than the immediate neighborhood.
                if ((nums[middle] < nums[middle - 1]) &&
                    nums[middle] < nums[middle + 1]){
                    min = nums[middle];
                    break;
                }
            }

            if (nums[middle] >= nums[left]){
                // Middle is in the left portion, search right.
                left = middle + 1;
                continue;;
            }

            if (nums[middle] < nums[left]){
                // Middle is in the right portion, search left.
                right = middle - 1;
                continue;
            }
        }
        return min;
    }
};

int main() {
    Solution sol;

    // Test case 1: typical case with rotation
    std::vector<int> testCase1 = {3, 4, 5, 1, 2};
    int result1 = sol.findMin(testCase1);
    std::cout << "Test case 1 - Expected: 1, Actual: " << result1 << std::endl;

    // Test case 2: array not rotated
    std::vector<int> testCase2 = {1, 2, 3, 4, 5};
    int result2 = sol.findMin(testCase2);
    std::cout << "Test case 2 - Expected: 1, Actual: " << result2 << std::endl;

    // Test case 3: rotation at the middle
    std::vector<int> testCase3 = {4, 5, 6, 7, 0, 1, 2};
    int result3 = sol.findMin(testCase3);
    std::cout << "Test case 3 - Expected: 0, Actual: " << result3 << std::endl;

    // Test case 4: rotation with duplicates (should not have duplicates as per problem statement)
    std::vector<int> testCase4 = {2, 2, 2, 0, 1};
    int result4 = sol.findMin(testCase4);
    std::cout << "Test case 4 - Expected: 0, Actual: " << result4 << std::endl;

    // Test case 5: single element array
    std::vector<int> testCase5 = {1};
    int result5 = sol.findMin(testCase5);
    std::cout << "Test case 5 - Expected: 1, Actual: " << result5 << std::endl;

    // Test case 6: two elements, rotated
    std::vector<int> testCase6 = {2, 1};
    int result6 = sol.findMin(testCase6);
    std::cout << "Test case 6 - Expected: 1, Actual: " << result6 << std::endl;

    // Test case 7: two elements, not rotated
    std::vector<int> testCase7 = {1, 2};
    int result7 = sol.findMin(testCase7);
    std::cout << "Test case 7 - Expected: 1, Actual: " << result7 << std::endl;

    // Test case 8: large array
    std::vector<int> testCase8 = {10, 20, 30, 40, 50, 5, 7, 9};
    int result8 = sol.findMin(testCase8);
    std::cout << "Test case 8 - Expected: 5, Actual: " << result8 << std::endl;

    return 0;
}