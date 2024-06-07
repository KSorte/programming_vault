#include <iostream>
#include <vector>

/**
 * @brief You are given an integer array height of length n.
 * There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 *
 * If a solution exists that doesn't have two heights on the edges, then this max must necessarily have a higher
 * minimum height.
 * Water capacity is a function of minimum height and distance. A max in the interior should mean a bigger min height.
 * So if you want to search for a max, you need to move the pointer with lower height inside.
 *
 * Steps for two pointer solution:
 * 1. Put two pointers on edges.
 * 2. max = 0
 * 3. A while loop (i < j)
 *  a. calculate W and compare with max; update max if needed.
 *  b. move lower pointer inside (i++ or j-- depending on who has lower height)
 * 4. Return max area.
 * @param height Vector of heights.
 * @returns Max water capacity in integer.
*/

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        // Initialize max_area to 0.
        int max_area = 0;
        // Initialize pointers.
        int i = 0, j = height.size() - 1;

        while (i < j){
            // Get current water capacity.
            auto water_capacity = (j - i)*std::min(height[i], height[j]);
            // max_area = std::max(max_area, water_capacity); Update max area.
            max_area = (water_capacity > max_area) ? water_capacity : max_area;
            // Move the pointer with lower height into the interior.
            if (height[i] <= height[j]) {
                i++;
            } else {
                j--;
            }
        }
        return max_area;
    }
};

int main() {
    Solution solution;

    // Test case 1
    std::vector<int> heights1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    std::cout << "Test case 1: " << solution.maxArea(heights1) << std::endl; // Expected output: 49

    // Test case 2
    std::vector<int> heights2 = {1, 1};
    std::cout << "Test case 2: " << solution.maxArea(heights2) << std::endl; // Expected output: 1

    // Test case 3
    std::vector<int> heights3 = {4, 3, 2, 1, 4};
    std::cout << "Test case 3: " << solution.maxArea(heights3) << std::endl; // Expected output: 16

    // Test case 4
    std::vector<int> heights4 = {1, 1, 1, 1};
    std::cout << "Test case 4: " << solution.maxArea(heights4) << std::endl; // Expected output: 2

    // Test case 5
    std::vector<int> heights5 = {2, 3, 4, 5, 18, 17, 6};
    std::cout << "Test case 5: " << solution.maxArea(heights5) << std::endl; // Expected output: 17

    // Test case 6
    std::vector<int> heights6 = {1, 8, 6, 2, 5, 4, 8, 25, 7};
    std::cout << "Test case 6: " << solution.maxArea(heights6) << std::endl; // Expected output: 49

    return 0;
}