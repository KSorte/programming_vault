#include <vector>

/*
    Leetcode 300 Longest Increasing Subsequence.
    Given an integer array nums, return the length of the longest strictly increasing
    subsequence.

    Algorithm:
    dp array where ith element is the length of the largest subsequence that
    ends at i.

    for each i
        iterate for j = 0, j < i

        if jth < ith
            dp ith = dp jth + 1.

    https://www.youtube.com/watch?v=cjWnW0hdF1Y
    DFS solution: DFS with cache.
    The time complexity can be reduced using binary search in the j iteration.
*/
class Solution {
public:
    /**
     * @brief Calculate the length of the largest increasing subsequence in the array of nums.
     * @param nums Vector of ints in which LIS needs to be found.
     * @returns Int length of the largest increasing subsequence.
     */
    int lengthOfLIS(std::vector<int>& nums) {
        // Get size.
        int n = nums.size();

        // Initialize Dp array.
        std::vector<int> dp_array(n, 1);
        int subsequence_len = 1;

        // O(n^2)
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
               if (nums[j] < nums[i]) {
                    // Update ith dp array element.
                    dp_array[i] = std::max(dp_array[j] + 1, dp_array[i]);

                    // Update LIS.
                    subsequence_len = std::max(dp_array[i], subsequence_len);
                    continue;
               }
            }
        }
        return subsequence_len;
    }
};