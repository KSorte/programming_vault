#include <vector>
#include <string>

/*
    Leetcode 91 Decode Ways
    https://leetcode.com/problems/decode-ways/description/

    Algorithm:
    Use 1 D DP, start from behind.

    For each position in the string, store the number of ways to decode if
    - Last two characters are combined.
    - Last two characters are not combined.

    Instead of using an array of pairs, store two pairs current and previous because at any moment during the execution you only
    need these two.

    In a for loop:
    if ith is 0 and i+1th is zero:
        return 0.

    if ith is 0:
        current_pair.first = previous_pair.first + previous_pair.second;
        current_pair.second = 0; continue;

    if i + 1 th is 0:
        if ith > 2 : return 0 (cannot form num.)

        // Can only combine with zero, get all ways from previous which was 0.
        current pair first = 0; current pair second = previous pair first.

    if ith > 2:
        // This character cannot combine because limit is 26.
        // Assign all previously found ways to first.

    if combined num > 26:
        continue;

    // get number of ways if ith is combined with i + 1th
    current_pair.second = previous_pair.first;
*/

class Solution {
public:
    /**
     * @brief Calculate number of ways to decode string.
     * @param s String to decode.
     * @returns Int number of ways to decode.
     */
    int numDecodings(std::string s) {
        this->s = s;
        if (s[0] == '0') {
            return 0;
        }

        int n = s.length();

        // number of ways to interpret last character.
        std::pair<int, int> previous_pair{0, 0};
        std::pair<int, int> current_pair{1, 0};

        // Initialize number of ways for last character.

        for (int i = n-2; i >= 0; i--) {
            previous_pair = current_pair;
            current_pair = {0, 0};
            if (s[i] == '0' && s[i+1] == '0') {
                return 0;
            }
            // Current character is 0.
            if (s[i] == '0') {
                // Assign all previously found ways to first.;
                current_pair.first = previous_pair.first + previous_pair.second;
                current_pair.second = 0;
                continue;
            }

            // Previous character is 0.
            if (s[i+1] == '0') {
                // String cannot form.
                if (get_num(i,1) > MAX_TENS_PLACE) {
                    return 0;
                }

                current_pair.first = 0;
                current_pair.second = previous_pair.first;
                continue;
            }

            if (get_num(i, 1) > MAX_TENS_PLACE) {
                // This character cannot combine because limit is 26.
                // Assign all previously found ways to first.
                current_pair.first = previous_pair.first + previous_pair.second;
                continue;
            }

            // Adding ith individually.
            current_pair.first = previous_pair.first + previous_pair.second;
            // Number combination is impossible.
            if (get_num(i, 2) > MAX_ALPHABET_NUMBER) {
                // If adding ith individually.
                continue;
            }

            // Combining ith with the i+1th character.
            current_pair.second = previous_pair.first;
        }
        return current_pair.first + current_pair.second;
    }

private:
    /**
     * @brief Convert string to int.
     * @param i Int index to convert.
     * @param j Int number of chars to consider.
     * @returns Int number converted from the string characters.
     */
    int get_num(int &i, int j) {
        return std::stoi(s.substr(i, j));
    }

    std::string s;

    // Max number of alphabets.
    static const int MAX_ALPHABET_NUMBER = 26;

    // Max number possible in tens place.
    static const int MAX_TENS_PLACE = 2;
};