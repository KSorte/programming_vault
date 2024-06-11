#include<iostream>
#include<unordered_map>
#include<vector>

/**
 * @brief Given an unsorted array of integers nums, return the length of the
 * longest consecutive elements sequence.
 * You must write an algorithm that runs in O(n) time.
 *
 * An unordered map doesn't allow for duplicate keys. For this problem, we may be given a vector with duplicates.
 * Adding it to a unordered map can help keep track of duplicates.
 *
 * The basic idea of this solution is to search for the end of a sequence and back-track it to
 * the start and notingt the sequence length.
 * This problem can also be solved by searching for sequence start.
 * In any case, middle elements in a sequence are skipped.
 *
 * Steps:
 * 1. Add all numbers to an unordered map and assign values to 0.
 * Lookup from an unordered map is O(1) time complexity.
 *
 * 2. Set max seq length = 0, and curr seq length to 1.
 *
 * 3. for num in nums:
 *  a. if element visited before -> skip
 *     if right neighbor found for element -> skip because it is not end of sequence.
 *  b. search_from = num;
 *  c. while (find_in_set(search_from - 1))   // If one less number is found.
 *      i. decrement search_from by 1.
 *      ii. current sequence length is incremented -> curr_seq ++.
 *  d. if curr_seq > max_seq_len -> update max_seq_len.
 *  e. Assign curr sequence length to num.
 *  f. curr_seq = 1 Reset curr sequence length
 *
 * 4. return maximum sequence length.
 * @param nums the integer array
 * @param k integer specifying the kth frequent food.
 * @returns Integer array returning the k most frequent elements in any order.
 */

class Solution {
public:

    int longestConsecutive(std::vector<int>& nums) {

        // Initialize an unordered map to map numbers to the max
        // sequence length behind that number.
        std::unordered_map<int, int> count_map;
        for (auto & num : nums){
            // Add number to map and assign max sequence as 0.
            count_map[num] = 0;
        }

        // Initialize max sequence and current sequence length.
        int max_seq_length = 0, curr_seq_length = 1;

        for (auto & num : nums){

            // If the number is visited before, skip.
            // Handles duplicates.
            if (count_map[num] != 0){
                continue;
            }

            if (count_map.find(num + 1) != count_map.end()){
                // If num is not end of sequence, do not process.
                continue;
            }

            // Assign current num to a search_from variable.
            auto search_from = num;

            // Search for a sequence backwards from search_from.
            // Continue while loop until one less element can't be found.
            while (count_map.find(search_from - 1) != count_map.end()) {  // O(1) search operation.
                search_from--; curr_seq_length++;
            }

            // Update max sequence length if a longer sequence found.
            max_seq_length =
                (curr_seq_length > max_seq_length) ? curr_seq_length : max_seq_length;

            // Assign current sequence length to the search from element.
            count_map[num] = curr_seq_length;

            // Reset current sequence length.
            curr_seq_length = 1;
        }
        return max_seq_length;
    }
};

/** NOTE.
 * The above approach is superior to the one using set.
 * This approach takes note of duplicates. For example -1, 1, 1, 2, 3, 4.
 * Using a set, the algorithm would compute the length 4 for both 1's.
 * Using a map, the algorithm would skip the second 1, because it has a non-zero
 * value assigned to it in the map.
*/

/**
 * SOLUTION FROM NEETCODE USING A HASH SET

    class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            unordered_set<int>s(nums.begin(), nums.end());
            int longest = 0;
            for(auto &n: s){
                //if this is the start of the sequence
                if(!s.count(n - 1)){
                    int length = 1;
                    while(s.count(n + length))
                        ++length;
                    longest = max(longest, length);
                }

            }
            return longest;
        }
    };
*/


int main() {
    Solution solution;

    // Test case 1
    std::vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    std::cout << "Test case 1: " << std::endl;
    std::cout << "Input: {100, 4, 200, 1, 3, 2}" << std::endl;
    std::cout << "Expected Output: 4" << std::endl;
    std::cout << "Actual Output: " << solution.longestConsecutive(nums1) << std::endl;
    std::cout << std::endl;

    // Test case 2
    std::vector<int> nums2 = {0,3,7,2,5,8,4,6,0,1};
    std::cout << "Test case 2: " << std::endl;
    std::cout << "Input: {0,3,7,2,5,8,4,6,0,1}" << std::endl;
    std::cout << "Expected Output: 9" << std::endl;
    std::cout << "Actual Output: " << solution.longestConsecutive(nums2) << std::endl;
    std::cout << std::endl;

    // Test case 3
    std::vector<int> nums3 = {0, -1, 1, 2, -2, 3};
    std::cout << "Test case 3: " << std::endl;
    std::cout << "Input: {0, -1, 1, 2, -2, 3}" << std::endl;
    std::cout << "Expected Output: 6" << std::endl;
    std::cout << "Actual Output: " << solution.longestConsecutive(nums3) << std::endl;
    std::cout << std::endl;

    // Test case 4
    std::vector<int> nums4 = {-6,-9,8,-8,-1,-3,-6,8,-9,-1,-4,-8,-5,0,1,6,-8,-5,-7,8,-2,-8,4,5,-5,-1,-5};
    std::cout << "Test case 4: " << std::endl;
    std::cout << "Input: {-6,-9,8,-8,-1,-3,-6,8,-9,-1,-4,-8,-5,0,1,6,-8,-5,-7,8,-2,-8,4,5,-5,-1,-5}" << std::endl;
    std::cout << "Expected Output: 11" << std::endl;
    std::cout << "Actual Output: " << solution.longestConsecutive(nums4) << std::endl;
    std::cout << std::endl;

    return 0;
}