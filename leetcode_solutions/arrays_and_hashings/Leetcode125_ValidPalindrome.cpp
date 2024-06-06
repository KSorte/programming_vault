#include<iostream>
#include <string>
#include <vector>

/**
 * @brief A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and
 * removing all non-alphanumeric characters, it reads the same forward and backward.
 * Alphanumeric characters include letters and numbers.
 *
 * Steps:
 * 1. Initialize two iterators one from the left (i) and another from the right(j)
 * 2. While loop (i < j)
    * i. if s(i) is not alphanumeric, i ++; do this in a loop until i < j.
    * ii. if s(j) is not alphanumeric, j --; do this in a loop until i < j.
    * iii. if lower case (s[i]) is not equal to lower case s[j], return false;
    * else i++ and j--.
 * Return True
 *
 * @param s the input string to be checked
 * @returns Boolean indicating whether the string is a palindrome or not.
 */

class Solution {
public:
    bool isPalindrome(std::string s) {

        // Initialize two iterators.
        int i = 0, j = s.size() - 1;

        while(i < j){

            // Check if ith char is alphanumeric; increment i if it is not.
            // Do this in a loop.
            while (!std::isalnum(s[i]) && (i < j)){
                i++;}

            // Check if jth char is alphanumeric; decrement j if it is not.
            // Do this in a loop.
            while (!std::isalnum(s[j]) && (i < j)){
                j--;}

            // If ith and jth characters (after converting to lower case) are not equal,
            // return false.
            if (std::tolower(s[i])!=std::tolower(s[j])){
                return false;
            } else {
                i++;
                j--;
            }
        }
        // Return true by default.
        return true;
    }
};

int main() {
    Solution solution;
    std::vector<std::pair<std::string, bool>> testCases = {
        {"A man, a plan, a canal: Panama", true},
        {"race a car", false},
        {" ", true},
        {"", true},
        {"0P", false},
        {"No lemon, no melon", true},
        {"Was it a car or a cat I saw?", true}
    };

    for (const auto& [testCase, expected] : testCases) {
        bool result = solution.isPalindrome(testCase);
        std::cout << "Input: \"" << testCase << "\"\n";
        std::cout << "Expected: " << std::boolalpha << expected << ", Got: " << result << "\n";
        std::cout << (result == expected ? "Test Passed" : "Test Failed") << "\n\n";
    }

    return 0;
}
