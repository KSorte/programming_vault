#include <iostream>
#include <vector>

/*
 Leetcode 121 Best Time to Buy And Sell Stock
 You are given an array prices where prices[i] is the price of a given stock on the ith day.

 You want to maximize your profit by choosing a single day to buy one stock and choosing a
 different day in the future to sell that stock.

 Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit,
 return 0.

 Two pointer approach:
 L = 0, R = 1
 max = 0
 while (R < size)
 if N(L) > N(R) : L = R, R ++
 (if Left is greater than R, then this is definitely a suboptimal buy - sell configuration
 Buy value should be as small as possible, hence immediately name L = R, and push R forward.)

 else R ++; Note down (R - L) and update max if needed.
*/

class Solution {
public:

    /**
     * @brief Calculate the maximum profit possible from a series of stock prices
     * @param prices Vector of integer stock prices
     * @returns Integer maximum profit.
     */
    int maxProfit(std::vector<int>& prices) {

        // Initialize max profit and buy - sell indices.
        int buy_index = 0, sell_index = 1, max_profit = 0;

        while(sell_index <= prices.size() - 1){
            if (prices[buy_index] > prices[sell_index]){
                // Buying price is greater, so push pointers forward.
                buy_index = sell_index;
                sell_index ++;
                continue;
            }

            // If there is net profit, note it down and push sell index forward
            auto current_profit = prices[sell_index] - prices[buy_index];
            // Update max profit
            max_profit = (max_profit > current_profit) ? max_profit : current_profit;
            sell_index ++;
        }
        return max_profit;
    }
};
