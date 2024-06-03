#include<iostream>
#include<unordered_map>
#include<vector>

/**
 * @brief Design an algorithm to encode a list of strings to a string.
 * The encoded string is then sent over the network and is decoded back to the original list of strings.
 *
 * Steps encode:
 * 1. Iterate through the vector of strings.
 * 2. Add str size, followed by | and actual string to encoded string.
 *
 * Steps decode:
 * 1. Iterate through the encoded string, one char at a time.
 * 2. If char is not |, it is a number.
 * Add this number to a len_str string.
 * 3. Once we reach the |, the len_str should hold the length of the string following |.
 * Convert len_str to integer using std::stoi and store in 'length'.
 * 4. Extract the string from index i + 1 onwards for length 'length' and add to decoded strings vector.
 */

class Codec {
public:

    /**
     * @brief  Encodes a list of strings to a single string delimited by |.
     * | is prefixed by string length.
     * @param strs Vector of strings to encode.
     * @returns Encoded string.
    */
    std::string encode(std::vector<std::string>& strs) {
        // Initialize encoded string
        std::string encoded_string;
        for (auto & str : strs){
            // Add str size, followed by | and actual string to encoded string.
            encoded_string += std::to_string(str.size()) + '|' + str;
        }
        return encoded_string;
    }

    /**
     * @brief  Decodes a single string to a list of strings.
     * @param s Encoded string.
     * @returns Vector of decoded strings.
    */
    std::vector<std::string> decode(std::string s) {

        // Initialize vector of decoded strings.
       std::vector<std::string> decoded_strings;

       // index iterator
       int i = 0;

       // String to store length of individual strings.
       std::string len_str;

       // Iterate through the encoded string.
       while (i < s.size()){
        // If s[i] is not |, it is a number; add it to len_str.
        if (s[i] != '|'){
            // Add the length character to the len_str
            len_str += s[i];
            i++;
            continue;
        }
        // if s[i] is |, get the length of the string in front of it
        auto length = std::stoi(len_str);
        // Add the string starting from index i+1 for length 'length to the decoded_strings vector.
        decoded_strings.emplace_back(s.substr(i + 1, length));
        // Re-initialize len_str
        len_str.clear();
        // Set i to the end of the string just extracted
        i = i + 1 + length;
       }
       return decoded_strings;
    }
};

int main() {
    Codec codec;

    // Test case 1: Empty input
    std::vector<std::string> input1;
    std::string encoded1 = codec.encode(input1);
    std::vector<std::string> decoded1 = codec.decode(encoded1);
    std::cout << "Test case 1: Empty input\n";
    std::cout << "Encoded string: " << encoded1 << std::endl;
    std::cout << "Decoded strings: ";
    for (const auto& str : decoded1) {
        std::cout << str << ", ";
    }
    std::cout << std::endl << std::endl;

    // Test case 2: Single string
    std::vector<std::string> input2 = {"hello"};
    std::string encoded2 = codec.encode(input2);
    std::vector<std::string> decoded2 = codec.decode(encoded2);
    std::cout << "Test case 2: Single string\n";
    std::cout << "Encoded string: " << encoded2 << std::endl;
    std::cout << "Decoded strings: ";
    for (const auto& str : decoded2) {
        std::cout << str << ", ";
    }
    std::cout << std::endl << std::endl;

    // Test case 3: Multiple strings
    std::vector<std::string> input3 = {"hello", "world", "foo", "bar"};
    std::string encoded3 = codec.encode(input3);
    std::vector<std::string> decoded3 = codec.decode(encoded3);
    std::cout << "Test case 3: Multiple strings\n";
    std::cout << "Encoded string: " << encoded3 << std::endl;
    std::cout << "Decoded strings: ";
    for (const auto& str : decoded3) {
        std::cout << str << ", ";
    }
    std::cout << std::endl << std::endl;
    return 0;
}