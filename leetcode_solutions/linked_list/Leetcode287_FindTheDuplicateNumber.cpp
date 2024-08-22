#include <vector>
/*
    Leetcode 287 Find the Duplicate Number
    Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

    There is only one repeated number in nums, return this repeated number.

    You must solve the problem without modifying the array nums and uses only constant extra space.

    Algorithm:
    Floyd's Algorithm. Not intuitive at all.
    https://www.youtube.com/watch?v=wjYnzkAhcNk
*/

class Solution {
public:
    /**
     * @brief Find duplicate number in a vector of size n + 1 containing ints from 1 to n.
     * @param nums Vector to search.
     * @returns Int that is repeated.
     */
    int findDuplicate(std::vector<int>& nums) {
        // Initialize slow, fast.
        int slow, fast = 0;

        // Step slow by 1, fast by 2.
        slow = nums[slow];
        fast = nums[nums[fast]];

        // First intersection point.
        while(slow != fast) {
            // Advance slow one step.
            slow = nums[slow];

            // Advance fast two steps.
            fast = nums[nums[fast]];
        }

        int new_slow = 0;
        // Second point of intersection.
        while(new_slow != slow) {
            slow = nums[slow];
            new_slow = nums[new_slow];
        }

        return slow;

    }
};