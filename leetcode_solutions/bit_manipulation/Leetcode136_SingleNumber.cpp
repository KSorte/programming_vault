#include <functional>  // for std::bit_xor
#include <numeric>  // for std::accumulate
#include <vector>

/*
    Leetcode 136 Single Number
    Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
    You must implement a solution with a linear runtime complexity and use only constant extra space.

    Algo:
    XOR all numbers in any order. All the repeated numbers will essentially get cancelled out.
    The result will be the single number.
*/

class Solution {
public:
    /**
     * @brief Return the number that appears exactly once.
     * @param nums Vector of ints
     * @returns Int appearing only once.
     */
    int singleNumber(std::vector<int>& nums) {
        return std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>());
    }

    int singleNumberForLoop(std::vector<int>& nums) {
        // Zeros do not change the XOR result, hence initializing with zeroes.
        int xor_result = 0;
        for (const auto & num : nums) {
            xor_result = xor_result ^ num;
        }  //xor_result would contain the single number.
        // All duplicated numbers cancel out in the xor operation.
        return xor_result;
    }
};


