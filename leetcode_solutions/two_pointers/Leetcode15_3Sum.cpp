#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @brief Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Here, they ask for the numbers themselves and not their indices unlike the two sum problem.
 * Notice that the solution set must not contain duplicate triplets.
 *
 * So sorting the array, fixing the first number and then implementing a version
 * of a two pointer algorihm to get the remaining two.
 *
 * std::sort(vec.begin(), vec.end()) ensures O(nlogn) time complexity.
 * Steps:
 * 1. Sort the input array using std::sort O(nlogn).
 * 2. Initialize a triplet vectors to hold triplets.
 * 2. Start a for loop with an i iterator; nums[i] fixes the first number in the triplet.
 *    a. Stop searching if ith num > 0; skip ith number if a duplicate.
 *    b. complement = target - nums[i]; j = i + 1; k = n - 1;
 *    c. if (jth + kth > complement) -> k--; if sum < complement -> j++
 *    d. if sum == target -> IF the combination (ith, jth and kth) NOT in triplet vectors:
 *          Add to triplet vector.
 *          j++ until a new jth and k -- until a new kth.
 * 3. Return triplet vector.
 *
 * @param nums input number vector
 * @returns A vector containing all unique triplets.
 */

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        // Triplet vector
        std::vector<std::vector<int>> triplet_vector;

        // Sort given number array in ascending order
        std::sort(nums.begin(), nums.end());

        // Initialize iterators.
        int i, j, k;
        i = 0;

        // This for loop is O(n)
        for(i = 0; i < nums.size(); i++){

            // If ith number > 0, stop searching.
            if (nums[i] > 0){
                break;
            }

            // Skip ith number if same as before to avoid duplicate triplets.
            if (i > 0 && nums[i] == nums [i - 1]){
                continue;
            }
            // Compute complement for the ith number.
            auto complement = 0 - nums[i];

            // Initialize j and k.
            j = i + 1, k = nums.size() - 1;

            // Start two pointer routine. O(n) worst case.
            while(j < k) {
                if (nums[j] + nums[k] < complement){
                    // If sum of j and k is smaller than complement, j++.
                    j++;
                } else if (nums[j] + nums[k] > complement){
                    // If sum of j and k is greater than complement, k--.
                    k--;
                } else {
                    // if ith + jth + kth == 0, add the triplet to the list.
                    triplet_vector.push_back({nums[i], nums[j], nums[k]});

                    // Increment j to skip over duplicate elements, to avoid
                    // Detecting the same triplet again.
                    while (j < k && nums[j] == nums[j + 1]){
                        j++;
                    }
                    j++;

                    // Decrement k to skip over duplicate elements, to avoid
                    // Detecting the same triplet again.
                    while (j < k && nums[k] == nums[k - 1]){
                        k--;
                    }
                k--;
                }
            }
        }
    return triplet_vector;
    }
};

int main() {
    Solution solution;

    std::vector<std::vector<int>> testCases = {
        {-1, 0, 1, 2, -1, -4},
        {0, 0, 0, 0},
        {-2, 0, 1, 1, 2},
        {3, -2, 1, 0},
        {-1, -1, -1, 2},
        {-2, 0, 0, 2, 2},
        {-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4},
        {-4, -2, -1},
        {1, 2, -2, -1},
        {-1, 0, 1, 0},
        {1, 1, -2, 0, -1}
    };

    for (const auto& testCase : testCases) {
        std::vector<std::vector<int>> result = solution.threeSum(const_cast<std::vector<int>&>(testCase));
        std::cout << "Input: ";
        for (int num : testCase) {
            std::cout << num << " ";
        }
        std::cout << "\nOutput:\n";
        for (const auto& triplet : result) {
            for (int num : triplet) {
                std::cout << num << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}