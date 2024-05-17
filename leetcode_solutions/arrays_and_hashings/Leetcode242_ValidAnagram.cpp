#include<iostream>
#include<map>

/**
 * @brief Determines if one string is an anagram of another.
 *
 * Given two strings s and t, this function returns true if t is an anagram of s, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * Steps:
 * 1. Create s_map and t_map to store the number of occurrences for each character in strings s and t.
 * 2. If s and t are anagrams, these maps will be identical since ordered maps store characters in
 *    order according to their ASCII values.
 *
 * @param s The first string.
 * @param t The second string.
 * @return A boolean indicating whether the two input strings are anagrams.
 */

class Solution {
public:
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
            std::cout<<it1->first<<" "<<it2->first<<std::endl;

            /* If s and t are anagrams, s_map and t_map maps are equal.
               If they are unequal, return false.
            */
            if(it1->second!=it2->second || it1->first!=it2->first) return false;
            it1++;
            it2++;
        }

        return true;
    }
};

int main()
{
    Solution solution;
    std::string s = "anagram";
    std::string t = "nagaram";
    std::cout<<std::boolalpha<<solution.isAnagram(s, t)<<std::endl;
}
