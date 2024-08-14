#include <iostream>
#include <cmath>

/*
Leetcode 190 Reverse Bits.
Reverse bits of a given 32 bits unsigned integer.

Algo:
    In a for loop i from 31 to 0:
        get last bit of n
        add last_bit* 2 ^ i to result.
        n = n >> 1

    return result;
*/
class Solution {
public:
    /**
     * @brief Reverse the bits of a 32 bits unsigned integer.
     * @param n uint32_t integer.
     * @returns uint32_t integer with reversed bits.
     */
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        for (int i = 31; i >= 0; i--) {
            // Get last bit.
            uint32_t last_bit = n & 1;

            // Add last bit raised to right power to result.
            result += last_bit*(1<<i);

            // Right shift.
            n = n >> 1;
        }
        return result;
    }
};


int main() {
    Solution s;
    uint32_t num1 = 4;
    auto res = s.reverseBits(num1);
    std::cout<<'\n';

    std::cout<<"Result = "<<res<<'\n';
    return 0;
}