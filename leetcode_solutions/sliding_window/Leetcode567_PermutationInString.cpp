#include <string>
#include <unordered_map>

/*
    Leetcode 567 Permutation In String
    Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

    In other words, return true if one of s1's permutations is the substring of s2.

    Steps:
    Unordered map for storing counts of given string.
    Unordered map for storing counts of a window in the target string.
    Add counts of first window to the window count map.
    m = size of input string whose perm needs to be checked.
    while (true):
        if (window count map == given map)
            return true

        slide window forward and adjust window count map.
        if (right + 1 is beyond end of string){
            break; We have reached the end of the target string.
        }
        window_count[right] ++;
        window_count[left] --;
        if  window_count[left] == 0
            remove window_count[left] from map.

    return false

*/
class Solution {
public:
    /**
     * @brief Check if permutations of a string exist in the second.
     * @param s1 String whose permutations are checked.
     * @param s2 String in which permutations of s1 are checked.
     * @returns Boolean indicating whether the permutations of s1 exist in s2.
     */
    bool checkInclusion(std::string s1, std::string s2) {
        if (s1.size() > s2.size()) {
            return false;
        }

        if (s1.size() == 0) {
            return true;
        }

        // Store frequency of s1 in a map.
        std::unordered_map<char, int> s1_freq;

        // Get frequencies.
        for (auto & character : s1) {
            s1_freq[character] ++;
        }

        // Map for storing frequencies of first window.
        std::unordered_map<char, int> window_freq;

        // Get frequencies of first window.
        for (int i = 0; i < s1.size(); i++) {
            window_freq[s2[i]] ++;
        }

        // Initialize sliding window.
        int left = 0, right = s1.size() - 1;
        while(true) {
            // check if both maps are equal
            if (s1_freq == window_freq) {
                // Permutation found in the current window
                return true;
            }

            if ((right) == s2.size() - 1) {
                // Right edge of window is already at the end of string s2.
                // Permutation not found.
                break;
            }

            // Increment right pointer.
            right ++;

            // Update frequencies of right and left pointers.
            window_freq[s2[right]] ++;
            window_freq[s2[left]] --;

            if (window_freq[s2[left]] == 0) {
                // Remove character at left edge if its count becomes 0.
                window_freq.erase(s2[left]);
            }

            // Increment left pointer.
            left ++;
        }

        return false;
    }
};