#include <vector>
/*
    Leetcode 198 House Robber
    https://leetcode.com/problems/house-robber/description/

    Algo:
    1. Create 1DP array storing the max profit theoretically possible until that house is reached (including that house.)
    2. Initialization of 0th and 1st elements.
    3. Iterate over remaining houses.
        dp[i] = max(dp[i - 1], dp[i - 1] + house[i])
    4. return last element. The max profits accumulate in the last element.

 */

class Solution {
public:
    /**
     * @brief Calculate the max profit possible for robbing houses in a street according to constraints.
     * @param nums Vector of ints representing houses.
     * @returns Int max profit possible.
     */
    int rob(std::vector<int>& nums) {
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
