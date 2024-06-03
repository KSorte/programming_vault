#include<iostream>
#include<unordered_map>
#include<vector>

/**
 * @brief Given an integer array nums and an integer k, return the k most frequent elements
 * within the array.
 * The test cases are generated such that the answer is always unique.
 * You may return the output in any order.
 *
 * Steps:
 * 1. Iterate through the integer array and create a map, mapping from integers to their counts.
 * 2. Create a vector of size n; elements of this vector are also vectors.
 * 3. Iterate through the map and append the integer key to the vector whose index corresponds to
 * the count of the integer in the map. So if the count of int 2 is 3, it is to be appended to the
 * third vector in the vector of vectors.
 * 4. Iterate through the bucket vector and a form a vector to return the k most frequent
 * elements.
 *
 * @param nums the integer array
 * @param k integer specifying the kth frequent food.
 * @returns Integer array returning the k most frequent elements in any order.
 */

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {

        // Map to assign counts to each integer
        std::unordered_map<int, int> count_map;
        auto n = nums.size();

        for (auto & num : nums){
            // Increment count for the integer iterated over.
            count_map[num]++;
        }

        // A bucket vector to group numbers according to their counts.
        std::vector<std::vector<int>> bucket_vector(n + 1);

        // Iterate through the map and sort integers into buckets.
        for (auto it = count_map.begin(); it != count_map.end(); it++){

            // Get index as the count of the integer being interated over.
            auto count = it->second;

            // Add the integer from the count map to the vector at index denoting its count.
            bucket_vector[count].emplace_back(it->first);
        }

        // Create vector for the k most frequent integers.
        std::vector<int> k_most_frequent_ints(k);
        // Integer to store count out of k.
        int count = 0;

        // Get k most frequent elements; iterate on bucket vector from the end.
        for(int i = bucket_vector.size()-1; i >= 0; i--){
            for (auto & number : bucket_vector[i]){
                k_most_frequent_ints[count] = number;
                count++;
                // Return vector after getting k most frequent elements
                if (count == k){
                    return k_most_frequent_ints;}
            }
        }
        return k_most_frequent_ints;
    }
};

int main() {
    Solution solution;

    // Test case 1: Typical case
    std::vector<int> nums1 = {1, 1, 1, 2, 2, 3};
    int k1 = 2;
    std::vector<int> result1 = solution.topKFrequent(nums1, k1);
    std::cout << "Test Case 1: ";
    for (int num : result1) std::cout << num << " ";
    std::cout << std::endl;

    // Test case 2: All elements are the same
    std::vector<int> nums2 = {1, 1, 1, 1};
    int k2 = 1;
    std::vector<int> result2 = solution.topKFrequent(nums2, k2);
    std::cout << "Test Case 2: ";
    for (int num : result2) std::cout << num << " ";
    std::cout << std::endl;

    // Test case 3: k is equal to the number of unique elements
    std::vector<int> nums3 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k3 = 10;
    std::vector<int> result3 = solution.topKFrequent(nums3, k3);
    std::cout << "Test Case 3: ";
    for (int num : result3) std::cout << num << " ";
    std::cout << std::endl;

    // Test case 4: k is 1
    std::vector<int> nums4 = {1, 2, 2, 3};
    int k4 = 1;
    std::vector<int> result4 = solution.topKFrequent(nums4, k4);
    std::cout << "Test Case 4: ";
    for (int num : result4) std::cout << num << " ";
    std::cout << std::endl;

    // Test case 5: nums contains negative numbers
    std::vector<int> nums5 = {-1, -1, -2, -2, -2, -3};
    int k5 = 2;
    std::vector<int> result5 = solution.topKFrequent(nums5, k5);
    std::cout << "Test Case 5: ";
    for (int num : result5) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}