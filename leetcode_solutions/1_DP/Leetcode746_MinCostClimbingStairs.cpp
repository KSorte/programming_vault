#include <vector>
/*
    Leetcode 746 Min Cost Climbing Stairs.
    You are given an integer array cost where cost[i] is the cost of ith step on a staircase.
    Once you pay the cost, you can either climb one or two steps.
    You can either start from the step with index 0, or the step with index 1.

    Return the minimum cost to reach the top of the floor.

    Algorithm:
    Create dp array of n + 1 storing min cost from each step upto the last step.
    We need to reach the top which is one beyond the last step.

    dp array[n] = 0; // Top.
    dp_array[n - 1] = cost[n - 1];

    for (i = n - 2, i >=0; i--) {
        dp_array[i] = cost[i] + min(dp_array[i+1], dp_array[i+2])

    return min of 0th and 1st.
    }
*/

class Solution {
public:
    /**
     * @brief Min cost to reach top from 0th or 1st step.
     * @param cost Vector of ints representing cost to pay at each step.
     * @returns Int minimum cost to reach the top.
     */
    int minCostClimbingStairs(std::vector<int>& cost) {
        int n = cost.size();

        if (n == 1) {
            return 0;
        }

        // Array to store min cost to go from a step to the end.
        std::vector<int> min_cost_from_step(n + 1, 0);

        // Cost 0 to reach top.
        min_cost_from_step[n] = 0;

        // Cost at last step.
        min_cost_from_step[n - 1] = cost[n - 1];

        for (int i = n-2; i>=0; i--) {
            // Min of i+1 and i+2 steps.
            min_cost_from_step[i] = cost[i] + std::min(min_cost_from_step[i + 1], min_cost_from_step[i + 2]);
        }

        return std::min(min_cost_from_step[0], min_cost_from_step[1]);
    }
};