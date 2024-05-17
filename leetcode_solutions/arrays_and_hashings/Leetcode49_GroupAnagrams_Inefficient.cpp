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
 * Step1: Utilize isAnagram function from Leetcode 242 problem to determine if two strings are anagrams.
 * Step2: Initialize the output anagram str vector and iterate through input vector of strings.
 * Step3: Check if the current string is an anagram to any of the anagram vectors.
 * Step4: Add to an anagram vector if the string is an anagram otherwise create a new anagram vector.
 * Step5: Retun the vector of anagrams.
 * @param strs Vector of strings
 * @returns A vector of vector of anagram strings.
 */

class Solution {
public:

    /**
     * @brief Function to determine if two strings are anagrams.
     * @param s The first string.
     * @param t The second string.
     * @return A boolean indicating whether the two input strings are anagrams.
     */
    bool isAnagram(std::string s, std::string t) {

        // Return false if the sizes of both strings are unequal.
        if (s.size()!=t.size()) return false;

        // Maps with string character as key and count as value.
        std::map<char, int> s_map;
        std::map<char, int> t_map;

        // Store the number of times a char occurs in s and t into maps.
        for (int i = 0; i<s.size(); i++)
        {
            // Increment the count of ith char in s
            s_map[s[i]]++;
            // Increment the count of ith char in t
            t_map[t[i]]++;
        }

        // Create iterators to iterate through the map.
        auto it1 = s_map.begin();
        auto it2 = t_map.begin();

        // Ordered maps store all the characters in the same order in both maps.
        while(it1!=s_map.end() && it2!=t_map.end())
        {
            /* If s and t are anagrams, s_map and t_map maps are equal.
               If they are unequal, return false.
            */
            if(it1->second!=it2->second || it1->first!=it2->first) return false;
            it1++;
            it2++;
        }

        return true;
    }
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {

        // Initialize vector of anagram string vectors to return.
        std::vector<std::vector<std::string>> anagram_strs;

        // Boolean to detemine if anagram is found.
        bool is_anagram_found;

        for (const auto str : strs){
            if(anagram_strs.size() == 0){
                // If anagram_strs size  = 0, create new anagram and add string to it.
                std::vector<std::string> anagrams;
                anagrams.emplace_back(str);
                anagram_strs.emplace_back(anagrams);
                continue;
            }
            for (auto & vector : anagram_strs){
                // Check if current iterated string is an anagram with existing anagram vectors.
                if(isAnagram(str, vector[0])){
                    // If an anagram group is found, add to it.
                    vector.emplace_back(str);
                    // Raise flag.
                    is_anagram_found = true;
                    // break for loop if an anagram found.
                    break;
                }
            }
            if(!is_anagram_found){
                // If an existing anagram is not found, create a new vector of anagrams.
                anagram_strs.emplace_back(std::vector<std::string>{str});
            }
            is_anagram_found = false;
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