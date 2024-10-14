#include <iostream>
#include <vector>
#include <string>
/*
Problem Description:
---------------------
You are given an array of strings, each composed of lowercase English letters.
Additionally, you are given several queries, where each query describes an index range [l, r]
in the string array (using 1-based indexing).

For each query, you are required to count how many strings in the specified index range start
and end with a vowel. Vowels are defined as any of the following letters: {a, e, i, o, u}.

Task:
-----
- Implement the function `hasVowels`, which takes in two parameters:
  1. A string array `strArr[]` containing n strings.
  2. A string array `query[]` containing q queries, where each query is in the format "l-r".

- For each query, you need to count how many strings within the range [l, r] (inclusive) start
  and end with a vowel.

Function Signature:
-------------------
vector<int> hasVowels(const vector<string>& strArr, const vector<string>& queries);

Example:
--------
Input:
strArr = ["aba", "bcb", "ece", "aa", "e"]
queries = ["1-3", "2-5", "2-2"]

Output:
[2, 3, 0]

Explanation:
------------
1. For the first query "1-3", strings at positions 1, 2, and 3 are considered. Out of these,
   the strings "aba" and "ece" start and end with a vowel. Therefore, the result is 2.

2. For the second query "2-5", strings at positions 2, 3, 4, and 5 are considered. Out of these,
   the strings "ece", "aa", and "e" start and end with a vowel. Therefore, the result is 3.

3. For the third query "2-2", only the string at position 2 is considered. The string "bcb" does
   not start and end with a vowel, so the result is 0.

Constraints:
------------
- 1 ≤ n, q ≤ 10^5
- 1 ≤ l ≤ r ≤ n
- 1 ≤ size of strArr[i] ≤ 10

Notes:
------
1. The query indices are 1-based.
2. You need to output the result for each query in the same order as the queries.
*/
// Helper function to check if a character is a vowel
bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Function to count strings that start and end with vowels in given intervals
std::vector<int> hasVowels(const std::vector<std::string>& strArr, const std::vector<std::string>& queries) {
    std::vector<int> result;
    for (const auto& query : queries) {
        // Parse the query, which is in the form "l-r"
        int dashPos = query.find('-');
        // Convert to 0-based index
        int l = stoi(query.substr(0, dashPos)) - 1;
        // Convert to 0-based index
        int r = stoi(query.substr(dashPos + 1)) - 1;

        // NOTE: Less fancy, but very short alternative leveraging the ASCII values.
        // int l = query[0] - '0' - 1;
        // int r = query[2] - '0' - 1;

        // Count the strings that start and end with a vowel in the range [l, r]
        int count = 0;
        for (int i = l; i <= r; ++i) {
            if (!strArr.empty() && isVowel(strArr[i][0]) && isVowel(strArr[i].back())) {
                count ++;
            }
        }
        result.push_back(count);
    }
    return result;
}

int main() {
    // Test Case 1: Basic example
    std::cout << "Test Case 1:" << std::endl;
    std::vector<std::string> strArr1 = {"aba", "bcb", "ece", "aa", "e"};
    std::vector<std::string> queries1 = {"1-3", "2-5", "2-2"};
    std::vector<int> result1 = hasVowels(strArr1, queries1);
    for (int res : result1) std::cout << res << " "; // Expected output: 2, 3, 0
    std::cout << std::endl << std::endl;

    // Test Case 2: All std::strings are vowels
    std::cout << "Test Case 2:" << std::endl;
    std::vector<std::string> strArr2 = {"a", "e", "i", "o", "u"};
    std::vector<std::string> queries2 = {"1-5", "1-3"};
    std::vector<int> result2 = hasVowels(strArr2, queries2);
    for (int res : result2) std::cout << res << " "; // Expected output: 5, 3
    std::cout << std::endl << std::endl;

    // Test Case 3: No std::strings start and end with vowels
    std::cout << "Test Case 3:" << std::endl;
    std::vector<std::string> strArr3 = {"bc", "df", "gh", "kl"};
    std::vector<std::string> queries3 = {"1-4", "1-2"};
    std::vector<int> result3 = hasVowels(strArr3, queries3);
    for (int res : result3) std::cout << res << " "; // Expected output: 0, 0
    std::cout << std::endl << std::endl;

    // Test Case 4: Mixed std::strings with some starting and ending with vowels
    std::cout << "Test Case 4:" << std::endl;
    std::vector<std::string> strArr4 = {"apple", "banana", "orange", "pear"};
    std::vector<std::string> queries4 = {"1-4", "2-3"};
    std::vector<int> result4 = hasVowels(strArr4, queries4);
    for (int res : result4) std::cout << res << " "; // Expected output: 2, 1
    std::cout << std::endl << std::endl;

    // Test Case 5: Single std::string with vowels at both ends
    std::cout << "Test Case 5:" << std::endl;
    std::vector<std::string> strArr5 = {"a"};
    std::vector<std::string> queries5 = {"1-1"};
    std::vector<int> result5 = hasVowels(strArr5, queries5);
    for (int res : result5) std::cout << res << " "; // Expected output: 1
    std::cout << std::endl << std::endl;

    // Test Case 6: Query with full range of std::strings
    std::cout << "Test Case 6:" << std::endl;
    std::vector<std::string> strArr6 = {"aba", "bcb", "cec", "ded", "eae"};
    std::vector<std::string> queries6 = {"1-5"};
    std::vector<int> result6 = hasVowels(strArr6, queries6);
    for (int res : result6) std::cout << res << " "; // Expected output: 2
    std::cout << std::endl << std::endl;

    // Test Case 7: Empty std::string array
    std::cout << "Test Case 7:" << std::endl;
    std::vector<std::string> strArr7 = {};
    std::vector<std::string> queries7 = {};
    std::vector<int> result7 = hasVowels(strArr7, queries7);
    for (int res : result7) std::cout << res << " "; // Expected output: No output
    std::cout << std::endl << std::endl;

    // Test Case 8: std::Strings with one character each
    std::cout << "Test Case 8:" << std::endl;
    std::vector<std::string> strArr8 = {"a", "b", "c", "d", "e"};
    std::vector<std::string> queries8 = {"1-5", "2-4"};
    std::vector<int> result8 = hasVowels(strArr8, queries8);
    for (int res : result8) std::cout << res << " "; // Expected output: 2, 0
    std::cout << std::endl << std::endl;

    // Test Case 9: Query with single std::string that doesn't start/end with vowels
    std::cout << "Test Case 9:" << std::endl;
    std::vector<std::string> strArr9 = {"bbc"};
    std::vector<std::string> queries9 = {"1-1"};
    std::vector<int> result9 = hasVowels(strArr9, queries9);
    for (int res : result9) std::cout << res << " "; // Expected output: 0
    std::cout << std::endl << std::endl;

    // Test Case 10: All std::strings have consonants at both ends
    std::cout << "Test Case 10:" << std::endl;
    std::vector<std::string> strArr10 = {"bbb", "ccc", "ddd", "fff"};
    std::vector<std::string> queries10 = {"1-4", "1-2"};
    std::vector<int> result10 = hasVowels(strArr10, queries10);
    for (int res : result10) std::cout << res << " "; // Expected output: 0, 0
    std::cout << std::endl << std::endl;

    return 0;
}
