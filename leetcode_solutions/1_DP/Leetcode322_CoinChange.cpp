#include <vector>
/*
    Leetcode 322 Coin Change
    You are given an integer array coins representing coins of different denominations and an integer amount representing a
    total amount of money.

    Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up
    by any combination of the coins, return -1.

    You may assume that you have an infinite number of each kind of coin.

    Algorithm:
    1 D Dynamic Programming problem.

    1. Create a dp array solving the problem for sum of 0, 1, 2, ...amount.
    2. assign 0 to 0th element.
    3. iterate from 1 to amount - 1
        Calculate the subproblem (i - coin) for each coin in the list.
    4. return last element in dp array.
*/

class Solution {
public:
    /**
     * @brief Calculate fewest number of coins needed to get the sum.
     * @param coins Vector of int coins
     * @param amount Int amount to reach.
     * @returns Int min number of coins needed to reach sum.
     */
    int coinChange(std::vector<int>& coins, int amount) {
        int num_coins = coins.size();

        // Dynamic programming array
        std::vector<int> sub_problems(amount + 1, amount + 1);

        // Base case.
        sub_problems[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (auto & coin : coins) {
                // j always < i
                int j = i - coin;

                if (j < 0) {
                    // Negative subcase.
                    continue;
                }

                if (sub_problems[j] == -1) {
                    // jth subproblem unsolvable.
                    continue;
                }

                sub_problems[i] = std::min(sub_problems[i], sub_problems[j] + 1);

            }
            if (sub_problems[i] == amount + 1) {
                // ith sub_problem not solved at all.
                sub_problems[i] = -1;
            }
        }

        return sub_problems[amount];
    }
};
