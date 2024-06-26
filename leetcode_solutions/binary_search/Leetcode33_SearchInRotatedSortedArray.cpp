#include <iostream>
#include <vector>

/*

Leetcode 33 Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown pivot index
k (1 <= k < nums.length) such that the resulting array is
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target
if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.

Solution 1: O(log(n)), find minimum first.
    The solution is an extension of the Leetcode 153 Find Minimum in Rotated Sorted Array problem.
    Find the minimum and then find the portion of the array where the target exists.
    Execute binary search on that portion.

Solution 2: Get target directly. Neetcode solution

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] <= target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};

*/

class Solution {
public:

    /**
     * @brief Search target in a rotated sorted integer array
     * @param nums Rotated sorted vector of integers
     * @param target Integer target to search for in rotated sorted array
     * @returns Integer index of target in the rotated sorted array
     */
    int search(std::vector<int>& nums, int target) {

        // Assign left and right to the ends of the array.
        int left = 0, right = nums.size() - 1;

        // Assign minimum to leftmost at the beginning.
        int min = nums[0];
        int min_index = -1;

        if (nums[left] > nums[right]){

            while (left <= right) {
                // First check if left and right flank a sorted portion.
                if (nums[left] <= nums[right]){
                    min = nums[left];
                    min_index = left;
                    break;
                }

                int middle = (left + right) / 2;
                // Check if middle is at a valley or a peak.
                if (middle != 0) {
                    // If middle element is greater than the immediate neighborhood.
                    if ((nums[middle] > nums[middle - 1]) &&
                        nums[middle] > nums[middle + 1]){
                        min = nums[middle + 1];
                        min_index = middle + 1;
                        break;
                    }
                    // If middle element is smaller than the immediate neighborhood.
                    if ((nums[middle] < nums[middle - 1]) &&
                        nums[middle] < nums[middle + 1]){
                        min = nums[middle];
                        min_index = middle;
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

            if (target >= nums[0]) {
                // target in the left portion
                left = 0, right = min_index - 1;
            } else {
                left = min_index, right = nums.size() - 1;
            }

        } else {
            min_index = 0;
        }

    int target_index = -1;

    // Do binary search on the portion of array defined by left and right.
    while(left <= right) {
        int middle = (left + right) / 2;
        if (nums[middle] == target) {
            target_index = middle;
            break;
        }
        if (nums[middle] > target) {
            right = middle - 1;
            continue;
        } else {
            left = middle + 1;
            continue;
        }
    }
    return target_index;
    }
};

int main() {
    Solution sol;

    // Test case 1: typical case with rotation
    std::vector<int> testCase1 = {3, 4, 5, 1, 2};
    int result1 = sol.search(testCase1, 4);
    std::cout << "Test case 1 - Expected: 1, Actual: " << result1 << std::endl;

    // Test case 2: array not rotated
    std::vector<int> testCase2 = {1, 2, 3, 4, 5};
    int result2 = sol.search(testCase2, 2);
    std::cout << "Test case 2 - Expected: 1, Actual: " << result2 << std::endl;

    // Test case 3: rotation at the middle
    std::vector<int> testCase3 = {4, 5, 6, 7, 0, 1, 2};
    int result3 = sol.search(testCase3, 0);
    std::cout << "Test case 3 - Expected: 4, Actual: " << result3 << std::endl;

    // Test case 4
    std::vector<int> testCase4 = {4,5,6,7,8,1,2,3};
    int result4 = sol.search(testCase4, 8);
    std::cout << "Test case 4 - Expected: 4, Actual: " << result4 << std::endl;
}