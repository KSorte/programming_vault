# include <iostream>
# include <string>

// In a uint8_t character.
#define NUM_BITS 8

/**
 * @brief Find number of 1's in the binary representation of a number.
 * @param str String input.
 * @returns Integer number of ones in the input string.
*/
int num_ones(std::string str) {
    int num_ones = 0;
    for (auto & c : str) {
        for (int i = 0; i < NUM_BITS; i++) {
            // AND
            auto last_bit = c & 1;

            // Count bit.
            if (last_bit == 1) {
                num_ones ++;
            }

            // Right Shift.
            c = c >> 1;
        }
    }
    return num_ones;
}

int main () {
    auto nums = num_ones("a");
    std::cout<<nums<<std::endl;
}