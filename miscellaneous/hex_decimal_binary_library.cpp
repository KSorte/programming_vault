#include <bitset>
#include <cstdint>
#include <iostream>

/*
    Refer this C++ documentation for std::hex, std::dec, and std::oct.
    https://en.cppreference.com/w/cpp/io/manip/hex
*/

int main() {
    // Example hexadecimal data array
    const uint8_t data[] = { 0xf2, 0xf2, 0xf2, 0xf2, 0xf2 };
    int data_length = sizeof(data) / sizeof(data[0]);

    std::cout << "Hexadecimal values:" << std::endl;
    for (int i = 0; i < data_length; ++i) {
        std::cout << "0x" << std::hex << +data[i] << std::endl;
    }

    std::cout << "\nDecimal values:" << std::endl;
    for (int i = 0; i < data_length; ++i) {
        std::cout << std::dec << +data[i] << std::endl;
        // std::cout << std::dec << static_cast<int>(data[i]) << std::endl;
    }

    std::cout << "\nOctal values:" << std::endl;
    for (int i = 0; i < data_length; ++i) {
        std::cout << std::oct << static_cast<int>(data[i]) << std::endl; // Equivalent.
        // std::cout << std::oct << +data[i] << std::endl;
    }
    std::cout << "The number 42 in binary:  " << std::bitset<8>{42} << '\n';
    return 0;
}