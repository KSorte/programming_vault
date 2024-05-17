#include <algorithm>
#include<iostream>
#include<map>
#include<vector>
/**
 * @brief Given an array of strings strs, group the anagrams together.
 * You can return the answer in any order.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * Steps for GroupAnagram()
 * Step1: Utilize a map assigning the anagram vector to a key representing anagram group.
 * Step2: Sort each input string to get anagram key for the string.
 * Step3: Group input string to appropriate anagram vector in map using key.
 * Step4: Create vector of anagram vectors and return.
 * @param strs Vector of strings
 * @returns A vector of vector of anagram strings.
 */

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {

        // Create an anagram map.
        std::unordered_map<std::string, std::vector<std::string>> anagram_map;

        // Iterate through the input strings to group them according to their anagrams.
        for (const auto str : strs){
            std::string sorted_str = str;
            // Sort the input string to use as a key.
            std::sort(sorted_str.begin(), sorted_str.end());
            // Add input str to vector associated with the key.
            anagram_map[sorted_str].emplace_back(str);
        }

        // Initialize vector of anagram string vectors to return.
        std::vector<std::vector<std::string>> anagram_strs;
        // Build result.
        for (auto it = anagram_map.begin(); it!=anagram_map.end(); it++){
            anagram_strs.emplace_back(it->second);
        }
        return anagram_strs;
    }
};

void printAnagramGroups(const std::vector<std::vector<std::string>>& anagramGroups) {
    std::cout << "[\n";
    for (const auto& group : anagramGroups) {
        std::cout << "  [ ";
        for (const auto& word : group) {
            std::cout << "\"" << word << "\", ";
        }
        std::cout << "],\n";
    }
    std::cout << "]\n";
}
int main(){
    Solution solution;
    // Test case 1
    std::vector<std::string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto result1 = solution.groupAnagrams(strs1);
    std::cout << "Test Case 1:\n";
    std::cout << "Input: [\"eat\", \"tea\", \"tan\", \"ate\", \"nat\", \"bat\"]\n";
    std::cout << "Output:\n";
    printAnagramGroups(result1);

    // Test case 2
    std::vector<std::string> strs2 = {""};
    auto result2 = solution.groupAnagrams(strs2);
    std::cout << "Test Case 2:\n";
    std::cout << "Input: [\"\"]\n";
    std::cout << "Output:\n";
    printAnagramGroups(result2);

    // Test case 3
    std::vector<std::string> strs3 = {"a"};
    auto result3 = solution.groupAnagrams(strs3);
    std::cout << "Test Case 3:\n";
    std::cout << "Input: [\"a\"]\n";
    std::cout << "Output:\n";
    printAnagramGroups(result3);

    // Test case 4
    std::vector<std::string> strs4 = {"abc", "bca", "cab", "dog", "god"};
    auto result4 = solution.groupAnagrams(strs4);
    std::cout << "Test Case 4:\n";
    std::cout << "Input: [\"abc\", \"bca\", \"cab\", \"dog\", \"god\"]\n";
    std::cout << "Output:\n";
    printAnagramGroups(result4);

    // Test case 5
    std::vector<std::string> strs5 = {"listen", "silent", "enlist", "google", "gogole"};
    auto result5 = solution.groupAnagrams(strs5);
    std::cout << "Test Case 5:\n";
    std::cout << "Input: [\"listen\", \"silent\", \"enlist\", \"google\", \"gogole\"]\n";
    std::cout << "Output:\n";
    printAnagramGroups(result5);

    return 0;
}