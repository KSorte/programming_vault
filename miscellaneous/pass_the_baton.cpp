#include <iostream>
#include <utility>
#include <cassert>

/**
 * PASS THE BATON
 * Determines which friend holds the baton and who will receive it at a given time.
 *
 * n friends stand in a line, each numbered from 1 to n. The baton starts at friend 1 (time = 0)
 * and is passed every second to the next friend. When the baton reaches the last
 * friend, the passing direction reverses. Given the number of friends and the time
 * in seconds, this function returns a pair of integers representing the friend
 * holding the baton and the next friend to receive it.
 *
 * ASSUMPTIONS:
 * n >= 2
 *
 * Algorithm:
 * 1. Num passes in each direction = n-1, passes in round trip back to 1 = 2n-2
 * 2. get number of trips: time / (2n-2), rem = time % (2n-2)
 * if rem <= n-1:
 *  Passing is still in forward part of the cycle.
 *  'rem' pass is done, baton passed from rem, rem+1.
 *
 * if rem > n-1:
 *  passing in reverse leg. get rem_rev = rem - (n-1)
 * 'rem_rev' pass done, baton passed from n - (rem_rev-1) to n - (rem_rev)
 */

class PassBaton {
public:
/**
 * @brief Return the current person holding the baton and the next person to pass to.
 * @param friends The total number of friends (1 to n).
 * @param time The number of seconds passed since the baton started being passed.
 * @return A pair of integers: the friend holding the baton and the next to receive it.
 */
    std::pair<int, int> baton_pass(int n, int time) {
        // Number of passes in one round trip.
        int cycle_length = 2*n-2;

        // Passes left after an integer number of trips are completed.
        int passes_left = time % cycle_length;

        // Initialize current and next to return.
        int current, next;
        if (passes_left < n-1) {
            // Forward portion.
            current = passes_left + 1;
            next = current + 1;
        } else if (passes_left >= n-1) {
            // Reverse portion.
            int passes_left_reverse = passes_left - n + 1;
            current = n - passes_left_reverse;
            next = current - 1;
        }

        // Return.
        std::pair<int, int> pair_of_friends(current, next);
        return pair_of_friends;
    }
};

/**
 * @brief Prints the result of a test case by comparing the actual output with the expected output.
 *
 * This function displays the expected and actual values for the test case. It then checks
 * if the result matches the expected value and prints "Passed" or "Failed" accordingly.
 *
 * @param result A pair of integers representing the actual result from the function being tested.
 * @param expected A pair of integers representing the expected output for the test case.
 * @param test_case_num An integer representing the test case number to be displayed for clarity.
 */

void print_result(const std::pair<int, int>& result, const std::pair<int, int>& expected, int test_case_num) {
    std::cout << "Test case " << test_case_num << ":\n";
    std::cout << "Expected: [" << expected.first << ", " << expected.second << "]\n";
    std::cout << "Actual: [" << result.first << ", " << result.second << "]\n";
    if (result == expected) {
        std::cout << "Result: Passed!\n\n";
    } else {
        std::cout << "Result: Failed!\n\n";
    }
}

int main() {
    auto pass_baton = PassBaton();

    // Test Case 1: friends = 4, time = 5
    std::pair<int, int> result = pass_baton.baton_pass(4, 5);
    print_result(result, {2, 1}, 1);

    // Test Case 2: friends = 4, time = 0
    result = pass_baton.baton_pass(4, 0);
    print_result(result, {1, 2}, 2);

    // Test Case 3: friends = 3, time = 4
    result = pass_baton.baton_pass(3, 4);
    print_result(result, {1, 2}, 3);

    // // Test Case 4: friends = 5, time = 10
    result = pass_baton.baton_pass(5, 10);
    print_result(result, {3, 4}, 4);

    // // Test Case 5: friends = 2, time = 3
    result = pass_baton.baton_pass(2, 3);
    print_result(result, {2, 1}, 5);

    return 0;
}