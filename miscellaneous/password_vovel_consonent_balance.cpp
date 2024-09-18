# include <algorithm>
# include <iostream>
# include <queue>
# include <vector>
# include <cassert>

/*
 * Problem: Given a password (string of lowercase English letters), modify it
 * so that the number of vowels is equal to the number of consonants.
 *
 * Vowels: 'a', 'e', 'i', 'o', 'u'.
 *
 * Operations: In one operation, you can either increment or decrement
 * any character by 1 (lexicographically).
 * Constraints:
 * - 'a' cannot be decremented.
 * - 'z' cannot be incremented.
 *
 * Goal: Find the minimum number of operations required to make the number
 * of vowels equal to the number of consonants.
 * Constraint: The number of letters in the password is always even.
 *
 * Algorithm:
 *  1. Count and store number of vowels and consonents in the password. Store the min distance of each consonent from the nearest vowel.
 *      Create a pairs of (dist from vowels, consonent) and add it to a min heap.
 *  2. if the num vowels == num consonentss:
 *      return 0;
 *  3. If the vowels > consonents
 *          Increment the required number of vowels.
 *  4. if vowels < consonents
 *          find the number of consonents needed to be turned into vowels -> op
 *          Turn the top op consonents into vowels and add the number of operations needed for it.
 */


class PasswordManagement {
public:
    /**
     * @brief Calculate the minimum number of operations to equalize the number of vowels and consonants in a password.
     *
     * This function counts the number of vowels and consonants in the given password. If the number of vowels
     * is greater than the number of consonants, it converts the necessary number of vowels to consonants,
     * and if consonants are greater, it converts consonants into vowels. Each consonant has an associated
     * cost of conversion to its nearest vowel, which is minimized by using a priority queue.
     *
     * @param password A string consisting of lowercase English letters representing the password.
     * @returns Integer representing the minimum number of operations required.
     */
    int min_operations(std::string password) {
        // Priority queue for storing min distance of consonents from vowels.
        std::priority_queue<
            std::pair<int, char>,
            std::vector<std::pair<int, char>>,
            std::greater<std::pair<int, char>>> consonent_distance;

        int num_vowels = 0, num_consonents = 0;

        // Iterate over password.
        int index = 0;
        for (const char & c : password){
            if (c == 'a' ||
                c == 'e' ||
                c == 'i' ||
                c == 'o' ||
                c == 'u') {
                    // Vowel
                    num_vowels ++;
            } else {
            // Consonent
            num_consonents ++;
            // Find distance from nearest vowel.
            auto min_dist_to_vowel = std::min({
                std::abs(c - 'a'),
                std::abs(c - 'e'),
                std::abs(c - 'i'),
                std::abs(c - 'o'),
                std::abs(c - 'u'),
            });

            consonent_distance.push({min_dist_to_vowel, c});
            }
            index ++;
        }

        int num_operations = 0;
        if (num_consonents == num_vowels){
            // Already balanced.
            num_operations = 0;
        } else if(num_vowels > num_consonents) {
            // Change required number of vowels to consonents.
            num_operations = (num_vowels - num_consonents)/2;
        } else {
            // Change required number of consonents to vowels and count number of operations.
            int num_consonents_to_change = (num_consonents - num_vowels)/2;
            for (int i = 0; i < num_consonents_to_change; i++) {
                auto consonent = consonent_distance.top();
                consonent_distance.pop();
                num_operations += consonent.first;
            }
        }
        return num_operations;
    }

    /**
     * @brief Runs a single test case for the min_operations function.
     *
     * This function tests the min_operations method by comparing its output with an expected value.
     * It prints whether the test passed or failed based on the comparison.
     *
     * @param password A string representing the password to be tested.
     * @param expected An integer representing the expected output.
     * @param test_case_number An integer representing the test case number for identification.
     */
    void run_test_case(const std::string& password, int expected, int test_case_number) {
        int result = min_operations(password);
        std::cout << "Test Case " << test_case_number << ": ";
        if (result == expected) {
            std::cout << "Passed!" << std::endl;
        } else {
            std::cout << "Failed. Expected " << expected << ", but got " << result << "." << std::endl;
        }
    }
};

int main() {
    PasswordManagement pm;

    // Test Case 1: Already balanced
    pm.run_test_case("abcdeu", 0, 1);

    // Test Case 2: Vowels > Consonants
    pm.run_test_case("aeiouuu", 3, 2);

    // Test Case 3: Consonants > Vowels
    pm.run_test_case("bcdfgh", 3, 3);

    // Test Case 4: Few operations required
    pm.run_test_case("bciopk", 1, 4);

    // Test Case 5: One consonant needs to be changed
    pm.run_test_case("aeiouc", 2, 5);

    // Test Case 6: Mixed
    pm.run_test_case("abcdef", 1, 6);

    // Test Case 7: Maximum imbalance
    pm.run_test_case("bbbbbbbb", 4, 7);

    return 0;
}