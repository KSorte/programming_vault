#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
/*
 * Problem: Sub-Palindromes
 *
 * A palindrome is a string that reads the same forward and backward, e.g. "121" or "tacocat".
 * A substring is a contiguous subset of characters in a string.
 * Given a string `s`, the goal is to find how many distinct substrings of `s` are palindromes.
 *
 * Example:
 * Input: s = "mokkori"
 *
 * Some of its substrings are:
 * [m, o, k, k, r, i, mo, ok, mok, okk, kk, okko]
 * There are 7 distinct palindromes:
 * [m, o, k, r, i, kk, okko]
 *
 * Function Description:
 * Complete the function `palindrome` which takes in a string `s` and returns the number of distinct palindromic substrings.
 *
 * Parameters:
 * string s: a string of length 1 <= |s| <= 5000
 *
 * Returns:
 * int: the number of distinct palindromes
 *
 * Constraints:
 * - The string length is at most 5000 characters.
 */

/*
 * This C++ solution solves the problem of finding distinct palindromic substrings in a string.
 * We use a technique called "Expand Around Center" to find all palindromes in O(n^2) time.
 * The approach works as follows:
 * 1. For each character in the string, treat it as the center of an odd-length palindrome.
 * 2. For each pair of adjacent characters, treat them as the center of an even-length palindrome.
 * 3. Expand around these centers to find all palindromes, and store them in an unordered set to ensure distinctness.
 * 4. Finally, return the size of the set, which gives the number of distinct palindromic substrings.
 * Time Complexity: O(n^2) where n is the length of the string.
 */

class Palindrome {
public:
    Palindrome() {
    }
    /**
     * @brief Counts the number of distinct palindromes in the input string.
     * @param word String input word.
     * @returns Integer number of distinct palindromes.
     */
    int count_palindrome(std::string word) {
        palindromes.clear();
        for (int i = 0; i < word.size(); i++) {
            expand_around_center(i, i, word);
            expand_around_center(i, i+1, word);
        }

        // Size of the set.
        return palindromes.size();
    }

    // TODO(KSorte): Fix this function
    int palindrome_dynamic_programming(std::string word) {
        palindromes.clear();
        size_t len = word.size();

        // Dp Array.
        std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, 0));

        // Single character palindromes
        for (int i = 0; i < len; i++) {
            dp[i][i] = true; // Each character is a palindrome
            palindromes.insert(word.substr(i, 1));
        }

        // Two character palindromes
        for (int i = 0; i < len - 1; i++) {
            if (word[i] == word[i + 1]) {
                dp[i][i + 1] = true; // Substring of length 2 is a palindrome
                palindromes.insert(word.substr(i, 2));
            }
        }

        // Check for palindromes length 3 or greater.
        for (int len_curr = 2; len_curr < len; len_curr++) {
            for (int start = 0; start < len - len_curr; start++) {
                int end = start + len_curr - 1;
                if (word[start] == word[end] && dp[start + 1][end-1]) {
                    // Is a palindrome.
                    dp[start][end] = true;
                    palindromes.insert(word.substr(start, len_curr));
                }
            }
        }
        return palindromes.size();
    }

private:

/**
 * @brief Executes expand around center operation around 1 or 2 letters until it ceases to be a palindrome or reaches
 * the end of the string
 * @param left Integer left index of the palindrome to check
 * @param right Integer right index of the palindrome to check
 * @param word Word to check for distinct palindromes.
 */
void expand_around_center(int left, int right, const std::string & word) {
    while (left >=0 && right < word.size() && word[left] == word[right]) {
        // Check if left, right within bounds and are equal.
        palindromes.insert(word.substr(left, right - left + 1));
        left --;
        right ++;
    }
}

// Set to store all distinct palindromes.
std::unordered_set<std::string> palindromes;
};

int main() {
    // Instantiate the Palindrome class
    Palindrome palindrome_test;

    // Test cases
    std::string test_cases[] = {
        "mokkori",        // Regular case with mixed-length palindromes
        "abba",           // Palindromes with even-length
        "racecar",        // Palindromes with odd-length
        "a",              // Single character (edge case)
        "abc",            // No repeated characters
        "aa",             // Two identical characters (edge case)
        "aaaa",           // All characters the same
        "abcba",          // Odd length palindrome in the middle
        "",               // Empty string (edge case)
        "abcdcbaabcdcba"  // Multiple embedded palindromes
    };

    // Expected number of distinct palindromes for each test case
    int expected_results[] = {
        7,   // "m", "o", "k", "r", "i", "kk", "okko"
        4,   // "a", "b", "bb", "abba"
        7,   // "r", "a", "c", "e", "cec", "aceca", "racecar"
        1,   // "a"
        3,   // "a", "b", "c"
        2,   // "a", "aa"
        4,   // "a", "aa", "aaa", "aaaa"
        5,   // "a", "b", "c", "bcb", "abcba"
        0,   // No palindromes (empty string)
        14   // "a", "b", "c", "d", "bcb", "dcd", "cdc", "abcdcba", "bcdcb", "baabcdcbab", "abcdcbaabcdcba"
    };

    // Running test cases
    for (int i = 0; i < 10; i++) {
        int result = palindrome_test.count_palindrome(test_cases[i]);

        std::cout << "Test case " << i + 1 << " (" << test_cases[i] << "): "
                  << "Expected = " << expected_results[i]
                  << ", Result = " << result
                  << (result == expected_results[i] ? " [PASS]" : " [FAIL]")
                  << std::endl;
    }

    auto result_10 = palindrome_test.count_palindrome(test_cases[9]);


    return 0;
}
