#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

/*
 * Problem: Investable Periods
 * -----------------------------------
 * A trading firm predicts the stock prices of a commodity for the next n days.
 * We are given an array 'prices' of length n, where prices[i] represents the
 * stock price on the ith day.
 *
 * A period of consecutive days is considered "investable" if:
 * - The maximum price in the period is equal to a given value 'max_price', and
 * - The minimum price in the period is equal to a given value 'min_price'.
 *
 * Our task is to find the total number of investable periods, i.e., the number
 * of contiguous subarrays where the maximum and minimum prices are exactly
 * equal to 'max_price' and 'min_price' respectively.
 *
 * Example:
 * ----------
 * Input:
 *  n = 4, prices = [1, 2, 3, 2], max_price = 3, min_price = 2
 *
 * Output:
 *  3
 *
 * Explanation:
 * The investable periods are:
 *  - Subarray [2, 3] (minimum = 2, maximum = 3)
 *  - Subarray [3, 2] (minimum = 2, maximum = 3)
 *  - Subarray [3, 2] (single element)
 *
 * Constraints:
 * ------------
 * - 1 <= n <= 10^5 (number of days)
 * - 1 <= prices[i], max_price, min_price <= 10^9 (valid stock prices)
 *
 * Approach:
 * ---------
 * To solve the problem efficiently in O(n), we use a sliding window technique.
 * We keep track of the max and the min value within each window.
 * In the for loop, we keep expanding the window under consideration (right edge).
 * Inside the for loop, if we find that the max and min bounds exceed the max and min prices, then we move the left edge rightward
 * until the bounds are inside the given range.
 *
 */

int countInvestablePeriods(int n, const std::vector<int>& prices, int max_price, int min_price) {
    int count = 0;
    int start = 0;

    // Initialize the min and max values.
    int max_so_far = 0;
    int min_so_far = std::numeric_limits<int>::max();

    for (int end = 0; end < prices.size(); end ++) {
        // Update current max and min.
        max_so_far = std::max(max_so_far, prices[end]);
        min_so_far = std::min(min_so_far, prices[end]);

        // Check if the current window violates the max and min bounds.
        while (max_so_far > max_price || min_so_far < min_price) {
            if (start == end) {
                // Start caught up with end, this is like a reset condition.
                max_so_far = 0;
                min_so_far = std::numeric_limits<int>::max();
                start ++;
                break;
            }

            if (prices[start] == max_so_far) {
                // Start index is the max. Update max.
                max_so_far = *std::max_element(prices.begin() + start + 1, prices.end());
            }

            if (prices[start] == min_so_far) {
                min_so_far = *std::min_element(prices.begin() + start + 1, prices.begin() + end + 1);
            }
        }

        if (max_so_far == max_price && min_so_far == min_price) {
            count += start + 1;
        }
    }
    return count;
}

// Brute Force
// int countInvestablePeriods(int n, const std::vector<int>& prices, int max_price, int min_price) {
//     int investible_periods = 0;
//     int start = 0;

//     // Initialize the min and max values.
//     int max_so_far = 0;
//     int min_so_far = std::numeric_limits<int>::max();

//     for (int i = 0; i < prices.size(); i++) {
//         max_so_far = prices[i];
//         min_so_far = prices[i];
//         for (int j = i; j < prices.size(); j++) {
//             max_so_far = std::max(max_so_far, prices[j]);
//             min_so_far = std::min(min_so_far, prices[j]);

//             if (max_so_far == max_price && min_so_far == min_price) {
//                 investible_periods ++;
//             }
//         }
//     }

//     return investible_periods;
// }


int main() {
    // Test cases: each tuple contains (prices, max_price, min_price, expected_output)
    std::vector<std::tuple<std::vector<int>, int, int, int>> test_cases = {
        {{1, 2, 3}, 5, 0, 0},
        {{4, 4, 4}, 4, 4, 6},
        {{5, 1, 3, 1, 5}, 5, 1, 5},
        {{7}, 7, 7, 1},
        {{10}, 5, 2, 0},
        {{3, 3, 3, 3}, 3, 3, 10},
        {{1, 3, 1, 3, 1, 3}, 3, 1, 15},
        {{1, 2, 3, 4, 5}, 5, 1, 1},
        {{5, 4, 3, 2, 1}, 5, 1, 1},
        {{2, 5, 2, 5, 2}, 5, 2, 8}
    };

    // Iterate through test cases
    for (size_t i = 0; i < test_cases.size(); ++i) {
        const std::vector<int>& prices = std::get<0>(test_cases[i]);
        int max_price = std::get<1>(test_cases[i]);
        int min_price = std::get<2>(test_cases[i]);
        int expected = std::get<3>(test_cases[i]);

        int n = prices.size();
        int result = countInvestablePeriods(n, prices, max_price, min_price);

        std::cout << "Test case " << i + 1 << ":\n";
        std::cout << "Prices: ";
        for (int price : prices) {
            std::cout << price << " ";
        }
        std::cout << "\nMax Price: " << max_price << ", Min Price: " << min_price << "\n";
        std::cout << "Expected Output: " << expected << ", Got: " << result << "\n";
        std::cout << (result == expected ? "PASS" : "FAIL") << "\n";
        std::cout << "-------------------------------------\n";
    }

    return 0;
}