#include<iostream>
#include<vector>

/**
 * @brief Description: You are given a large integer represented as an integer array digits, where each
 * digits[i] is the ith digit of the integer. The digits are ordered from most significant to
 * least significant in left-to-right order. The large integer does not contain any leading 0's.
 * Increment the large integer by one and return the resulting array of digits.
 *
 * Steps:
 * Step1: Iterate through all digits from left to right.
 * Step2: Increment digit if not nine and return.
 * Step3: Set to zero if nine and continue.
 * If all digits are nine, set zeroth digit to 1 and add a zero.
 * @param digits Vector of int digits
 * @returns Vector of int digits with the number incremented by one.
*/

class Solution {
public:
    std::vector<int> plusOne(std::vector<int>& digits) {

    // Iterate through the digits array from least to most significant digit.
    for (int i=digits.size()-1; i>=0; i--)
    {
        if(digits[i] == 9) {
            // If a digit is 9, replace with 0 and abandon the iteration.
            digits[i] = 0;
            continue;
        } else {
            // Increment digit, if not nine.
            digits[i] += 1;
            // Return digits if digit incremented.
            return digits;
        }
    }   // for loop ends

    /**
     * Previously, I inserted a 1 at the beginning of the vector using vector.insert(vector.begin(), 1)
     * But that is an expensive operation.
     */
    // Increment 0th digit to 1 if all nines.
    digits[0] = 1;
    // Add a zero digit at the tail.
    digits.emplace_back(0);
    return digits;
    }
};

// Function to print the vector
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}


int main() {
    Solution solution;

    // Test case 1
    std::vector<int> digits1 = {1, 2, 3};
    std::vector<int> result1 = solution.plusOne(digits1);
    std::cout << "Test Case 1: ";
    printVector(result1); // Expected Output: [1, 2, 4]

    // Test case 2
    std::vector<int> digits2 = {4, 3, 2, 1};
    std::vector<int> result2 = solution.plusOne(digits2);
    std::cout << "Test Case 2: ";
    printVector(result2); // Expected Output: [4, 3, 2, 2]

    // Test case 3
    std::vector<int> digits3 = {9, 9, 9};
    std::vector<int> result3 = solution.plusOne(digits3);
    std::cout << "Test Case 3: ";
    printVector(result3); // Expected Output: [1, 0, 0, 0]

    return 0;
}

