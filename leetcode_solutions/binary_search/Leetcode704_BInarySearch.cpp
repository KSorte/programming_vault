#include <vector>

/*
    Leetcode 704 Binary Search.
    Given an array of integers nums which is sorted in ascending order, and an integer target,
    write a function to search target in nums. If target exists, then return its index.
    Otherwise, return -1.
    You must write an algorithm with O(log n) runtime complexity.

    Steps:
    1. Find the middle of the array.
    2. If start > end -> return not found
    2. If target > middle -> go right and do binary search
    3. If target < middle -> go left and do binary search
    4. If target == middle return target.

    This can be solved by recursion.
    Remove the while loop; the internal if logic remains the same.
    But when you reevaluate start and end, call the binary search function again with new start, end and target.
    Here the search function template doesn't lend itself to recursion since it takes the whole vector as input.
*/
class Solution {
public:

    /**
     * @brief Search array sorted in ascending order in O(logn) using Binary Search.
     * @param nums Vector to be searched.
     * @param target Target number
     * @returns Integer index of the target.
     */
    int search(std::vector<int>& nums, int target) {
        int n = nums.size();
        // Initialize start and end.
        int start = 0, end = n - 1, result = -1;

        // O(log(n)) loop
        while (start <= end) {
            // If start exceed ends, return -1 (failure).
            if (start > end) {
                result = -1;
                break;
            }

            int middle = (end + start)/2;
            // If middle is target, return it.
            if (target == nums[middle]) {
                result = middle;
                break;
            }

            // If target greater than middle, go right.
            if (target > nums[middle]) {
                start = middle + 1;
                continue;
            }

            // If target smaller than middle, go left.
            if (target < nums[middle]) {
                end = middle - 1;
                continue;
            }
        }
        return result;
    }
};