#include <vector>

/*
    Leetcode 268 Missing Number
    Given an array nums containing n distinct numbers in the range [0, n],
    return the only number in the range that is missing from the array.

    Algo:
    Calculate expected sum of the list and subtract from it the actual sum.

*/

class Solution {
public:
    /**
     * @brief Return the number that is missing from the array.
     * @param nums Vector of ints from 0 to n with exactly 1 number missing.
     * @returns Int missing number.
     */
    int missingNumber(std::vector<int>& nums) {
        auto n = nums.size();
        int expected_sum = n*(n + 1)/2;
        int sum = 0;
        for (const auto & num : nums) {
            sum += num;
        }
        return expected_sum - sum;
    }
};