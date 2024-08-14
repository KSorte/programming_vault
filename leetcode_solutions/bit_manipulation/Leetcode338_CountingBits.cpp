#include <vector>
/*
Leetcode 338 Counting Bits
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
ans[i] is the number of 1's in the binary representation of i.

Concept:
    the number of 1's in an odd integer is exactly 1 + the
    number of 1's in an even integer because even has last bit as 0;
    Doubling a number is simply left shifting it by 1 (Adding a 0 to the right).
    So the number of 1's in an even integer is same as the number of 1's
    in the number half of it.

    eg. num of 1's in 3 = num of 1's in 6.


*/
class Solution {
public:
    /**
     * @brief Gets the array of integers representing the number of 1's in each
     * number from 0 to n.
     * @param n
     * @returns Vector of int array of number of 1's in all ints from 0 to n.
     */
    std::vector<int> countBits(int n) {
        std::vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            result[i] = result[i/2] + i % 2;
            // result[i] = result[i>>2] + i & 1;
        }
        return result;
    }
};