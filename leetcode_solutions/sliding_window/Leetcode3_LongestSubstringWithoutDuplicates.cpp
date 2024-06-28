#include <iostream>
#include <string>
#include <unordered_set>

/*

    Leetcode 3 Longest Substring Without Duplicates.
    Given a string s, find the length of the longest substring without repeating characters.

    Two pointer approach - sliding window
    Initialize two pointers at 0 and 1 : l and r

    while r not at end:
        If s(r) exists in the previous substring(i.e. in the set) at i
            while s(l) not equal to s(r):
                set.remove(s(l))
                l ++;
            set.remove(s(l)); l++;

        if s(r) non-existent in the set,
            add s(r) to set.
            r ++.
        update max string length from the set size.
*/

class Solution {
public:

    /**
     * @brief Calculate the length of largest substring with no duplicates using
     * a sliding window approach.
     * @param s Input string to analyze for duplicates.
     * @returns Integer largest length of substring with no duplicates.
     */
    int lengthOfLongestSubstring(std::string s) {
        // Initialize set to store largest substring.
        std::unordered_set<char> set_longest_substring;

        if (s.size() <= 1) {
            // Return string size if it is not greater than 1.
            return s.size();
        }

        // Initialize sliding window pointers.
        int left = 0, right = 1;

        // Add character at left pointer to set.
        set_longest_substring.insert(s[left]);

        int length_longest_substring = 1;

        // While loop until right reaches the other end.
        while (right < s.size()) {
            // Check if character at right pointer exists in the set.
            if (set_longest_substring.find(s[right]) != set_longest_substring.end()) {
                // remove all characters in set upto the one that is equal to s(r).
                while (s[left] != s[right]) {
                    auto it = set_longest_substring.find(s[left]);
                    set_longest_substring.erase(it);
                    left ++;
                }  // while loop ends, s[left] = s[right]

                // remove this s[left] which is equal to s[right]
                auto it = set_longest_substring.find(s[left]);
                set_longest_substring.erase(it); left ++;
            } else {
                set_longest_substring.insert(s[right]);
                right ++;
            }  // sliding window adjustment ends here.

            // Check size of set
            length_longest_substring =
                (set_longest_substring.size() > length_longest_substring) ?
                set_longest_substring.size() : length_longest_substring;
        }  // O(n) iteration over string ends.

        return length_longest_substring;
    }
};

int main() {
    Solution solution;

    std::string test1 = "abcabcbb";
    std::cout << "Test 1: " << solution.lengthOfLongestSubstring(test1) << " (Expected: 3)" << std::endl;

    std::string test2 = "bbbbb";
    std::cout << "Test 3: " << solution.lengthOfLongestSubstring(test2) << " (Expected: 1)" << std::endl;

    std::string test3 = "pwwkew";
    std::cout << "Test 7: " << solution.lengthOfLongestSubstring(test3) << " (Expected: 3)" << std::endl;

    std::string test4 = "";
    std::cout << "Test 7: " << solution.lengthOfLongestSubstring(test4) << " (Expected: 0)" << std::endl;
}