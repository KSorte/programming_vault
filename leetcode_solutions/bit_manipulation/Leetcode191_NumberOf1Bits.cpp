/*
    Leetcode 191 Number of 1 Bits
    Write a function that takes the binary representation of a positive integer and returns the number of
    set bits it has (also known as the Hamming weight).

    Algo:
    AND with 1, to get last bit.
    Right shift by 1 bit.
*/


class Solution {
public:
    /**
     * @brief Get the number of 1 bits in the binary number.
     * @param n Integer number whose binary representation is considered.
     * @returns Integer number of 1 bits in the binary representation.
     */
    int hammingWeight(int n) {
        int set_bits = 0;

        while (n != 0) {
            set_bits += n & 1;
            n = n >> 1;
        }
        return set_bits;
    }
};