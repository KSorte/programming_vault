#include <vector>

/*
    Leetcode 70 Climbing Stairs.
    You are climbing a staircase. It takes n steps to reach the top.

    Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

    Method 1:
    Essentially finding nth term of Fibonacci Series.

    Method 2:
    Bottom's up dynamic programming approach for solving this. Start from the back.
*/

class Solution {
public:
    /**
     * @brief Calculate ways to climb a staircase.
     * @param n Integer number of stairs.
     * @returns Integer number of ways to climb staircase.
     */
    int climbStairs(int n) {
        // Edge cases.
        if (n <= 1) {
            return 1;
        }

        // Vector to store the number of ways to climb to each step.
        std::vector<int> ways_to_climb(n + 1);

        // Base cases; 1 way to top for both.
        ways_to_climb[n] = 1, ways_to_climb[n - 1] = 1;

        // Calculate ways to climb from (n - 2)th step to the 0th step.
        for (int i = n - 2; i >= 0; i --) {
            ways_to_climb[i] = ways_to_climb [i + 1] + ways_to_climb[i + 2];
        }

        // Return number of ways from step 0.
        return ways_to_climb[0];

    // METHOD 2.
    //   int f = 1; int s = 1; int sum = 1; //initilizing all three variables
    //   for (int i = 2; i<=n; i++){
    //       sum = f + s;
    //       f = s;
    //       s = sum;
    //       }
    //       return sum;
    }
};