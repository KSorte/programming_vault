#include <iostream>
#include <string>
#include <unordered_map>
/*
Leetcode 424 Longest Repeating Character Replacement
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character.
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Sliding Window Approach:
A window is valid if (window_size - character_count_max) <= k.
If the window is valid -> store the size.
    Increment right limit.
If the window is invalid because the difference is greater than the replacements available
    left ++;

TODO(KSorte): CREATE A NEW CLASS TO HANDLE POINTER AND COUNT UPDATES.
(Essentially make the code more adherent to SOLID.)
    * Create a class with following attibutes
        unordered map
        count most occuring character.

    * Have the following methods inside the class.
    increment_right():
        right++;
        sliding_window_char_frequencies[s[right]] ++;
        count_most_occuring_letter = std::max(count_most_occuring_letter, sliding_window_char_frequencies[s[right]]);

   *  increment_left():
     sliding_window_char_frequencies[s[left]] --;

                // Update count of most occuring letter.
                count_most_occuring_letter = 0;
                for (auto char_count_pair = sliding_window_char_frequencies.begin();
                    char_count_pair != sliding_window_char_frequencies.end();
                    char_count_pair ++) {
                        count_most_occuring_letter = std::max(count_most_occuring_letter, char_count_pair->second);
                    }
                left ++;

    * get_count_most_frequent()
        retunr count most occuring character
*/

class Solution {
public:
    int characterReplacement(std::string s, int k) {
        // If input string size = 1
        if (s.size() == 1) {
            return 1;
        }

        // Map for storing frequencies of sliding window.
        std::unordered_map<char, int> sliding_window_char_frequencies;
        // Initialize sliding window.
        int left = 0, right = 0;
        int count_most_occuring_letter;

        // First window character frequencies.
        sliding_window_char_frequencies[s[left]] ++;
        count_most_occuring_letter = 1;
        int longest_substring = 1;

        while(true) {
            int window_size = right - left + 1;
            int needed_replacements = window_size - count_most_occuring_letter;

            // Update sliding window and counts.
            if (needed_replacements <= k) {
                // Valid window. Update longest substring.
                longest_substring =
                    std::max(longest_substring, window_size);

                if (right == s.size() - 1) {
                    // Window at end of string.
                    break;
                }

                // Increment right, counts and count most occuring letter.
                right ++;
                sliding_window_char_frequencies[s[right]] ++;
                count_most_occuring_letter = std::max(count_most_occuring_letter, sliding_window_char_frequencies[s[right]]);
            } else {
                // Invalid window, slide left.
                sliding_window_char_frequencies[s[left]] --;

                // Update count of most occuring letter.
                count_most_occuring_letter = 0;
                for (auto char_count_pair = sliding_window_char_frequencies.begin();
                    char_count_pair != sliding_window_char_frequencies.end();
                    char_count_pair ++) {
                        count_most_occuring_letter = std::max(count_most_occuring_letter, char_count_pair->second);
                    }
                left ++;
            }

        }
        return longest_substring;
    }
};

int main() {
    Solution s;
    std::string test = "ABAB";
    int res = s.characterReplacement(test, 2);
    std::cout<<"Longest substring: " << res <<std::endl;
}

/*
REFACTORED CODE FOR MORE READABILITY

#include <iostream>
#include <string>
#include <unordered_map>

class FrequencyCounter {
public:
    void increment(char c) {
        frequencies[c]++;
        max_frequency = std::max(max_frequency, frequencies[c]);
    }

    void decrement(char c) {
        frequencies[c]--;
        if (frequencies[c] == 0) {
            frequencies.erase(c);
        }
        recalculateMaxFrequency();
    }

    int getMaxFrequency() const {
        return max_frequency;
    }

private:
    std::unordered_map<char, int> frequencies;
    int max_frequency = 0;

    void recalculateMaxFrequency() {
        max_frequency = 0;
        for (const auto& pair : frequencies) {
            max_frequency = std::max(max_frequency, pair.second);
        }
    }
};

class Solution {
public:
    int characterReplacement(const std::string& s, int k) {
        if (s.size() == 1) {
            return 1;
        }

        FrequencyCounter frequency_counter;
        int left = 0, right = 0;
        frequency_counter.increment(s[left]);
        int longest_substring = 1;

        while (true) {
            int window_size = right - left + 1;
            int needed_replacements = window_size - frequency_counter.getMaxFrequency();

            if (needed_replacements <= k) {
                longest_substring = std::max(longest_substring, window_size);

                if (right == s.size() - 1) {
                    break;
                }

                right++;
                frequency_counter.increment(s[right]);
            } else {
                frequency_counter.decrement(s[left]);
                left++;
            }
        }

        return longest_substring;
    }
};

int main() {
    Solution solution;
    std::string test = "ABAB";
    int result = solution.characterReplacement(test, 2);
    std::cout << "Longest substring: " << result << std::endl;  // Expected output: 4

    return 0;
}







*/