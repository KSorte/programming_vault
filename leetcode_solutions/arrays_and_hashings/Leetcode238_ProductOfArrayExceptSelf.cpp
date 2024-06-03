#include<iostream>
#include<vector>
/**
 * @brief Given an integer array nums, return an array answer such that answer[i]
 * is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * The approach to solve this is to compute the product of all prefixes and suffixes of
 * of a particular in an array through two passes.
 *
 * Steps:
 *
 * Step1. Initialize an product array(PA) of size n to hold the product
 * initialize prefex product (PP) to 1.
 * initialize suffix product (SP) to 1.
 *
 * Step2. For loop through the array from 0 to n-1;
 * At ith iteration assign PP to the ith place in PA.
 * Multiply ith array element to PP and end the iteration.
 *
 * Step3. For loop through the array from n-1 to 0;
 * At ith iteration, multiply SP to the ith element in PA.
 * Multiply the ith element in given array to SP to update it and end iteration.
 *
 * Step4: Return Product Array.
 */

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
    // Initialize suffix and prefix product.
    int prefix_product = 1, suffix_product = 1;

    // Initialize product array to return of size equal to the given array.
    std::vector<int> product_array(nums.size());

    // Forward pass through the given array to store prefix products.
    for (int i = 0; i < nums.size(); i++){
        // Assign prefix product to the corresponding place in the product array.
        product_array[i] = prefix_product;
        // Update prefix product with the latest number.
        prefix_product *= nums[i];
    }

    // Backward pass through the given array to get suffix products.
    for (int i = nums.size()-1; i >= 0; i--){
        // Multiply suffix product with the corresponding prefix product to get
        // whole product
        product_array[i] *= suffix_product;
        // Update suffix product with the latest number.
        suffix_product *= nums[i];
    }
    return product_array;
    }
};

int main() {
    Solution sol;

    // Test case 1
    std::vector<int> nums1 = {1, 2, 3, 4};
    std::vector<int> result1 = sol.productExceptSelf(nums1);
    std::cout << "Test case 1: ";
    for (int num : result1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;  // Expected output: 24 12 8 6

    // Test case 2
    std::vector<int> nums2 = {5, 6, 7, 8};
    std::vector<int> result2 = sol.productExceptSelf(nums2);
    std::cout << "Test case 2: ";
    for (int num : result2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;  // Expected output: 336 280 240 210

    // Test case 3
    std::vector<int> nums3 = {0, 1, 2, 3};
    std::vector<int> result3 = sol.productExceptSelf(nums3);
    std::cout << "Test case 3: ";
    for (int num : result3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;  // Expected output: 6 0 0 0

    // Test case 4
    std::vector<int> nums4 = {-1, 1, 0, -3, 3};
    std::vector<int> result4 = sol.productExceptSelf(nums4);
    std::cout << "Test case 4: ";
    for (int num : result4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;  // Expected output: 0 0 9 0 0

    return 0;
}