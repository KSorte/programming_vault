#include <vector>

/*
    Leetcode 213 House Robber II
    https://leetcode.com/problems/house-robber-ii/

    Algorithm:
    The first and the last house can't be robbed at the same time.
    So to tackle this, solve two dp problems for houses 0 to n -2 and houses 1 to n-1
    and get the max of those.

*/
class Solution {
public:
    /**
     * @brief Calculate the max profit possible for robbing houses in on a circular street according to constraints.
     * @param nums Vector of ints representing houses.
     * @returns Int max profit possible.
     */
    int rob(std::vector<int>& nums) {
        int num_houses = nums.size();

        if (num_houses == 1) {
            // This case matters for checking 1 to n - 1 elements.
            return nums[0];
        }

        // For checking from 0 to n - 2 elements.
        std::vector<int> nums1(nums.begin(), nums.end() - 1);

        // For checking from 1 to n - 1 elements.
        std::vector<int> nums2(nums.begin() + 1, nums.end());

        return std::max(rob1_(nums1), rob1_(nums2));
    }

private:
    /**
     * @brief Calculate the max profit possible for robbing houses in on a straight street according to constraints.
     * @param nums Vector of ints representing houses.
     * @returns Int max profit possible.
     */
    int rob1_(std::vector<int>& nums) {
        int num_houses = nums.size();

        if (num_houses == 1) {
            return nums[0];
        }

        // DP Array to store the maximum profit theoretically possible until
        // that house.
        std::vector<int> dp_array(num_houses, 0);

        // Initialization
        dp_array[0] = nums[0];
        dp_array[1] = std::max(dp_array[0], nums[1]);

        // Max possible profit accumulates at the end of the array.
        for (int i = 2; i < num_houses; i++) {
            dp_array[i] = std::max(dp_array[i - 2] + nums[i], dp_array[i - 1]);
        }

        return dp_array[num_houses - 1];
    }
};