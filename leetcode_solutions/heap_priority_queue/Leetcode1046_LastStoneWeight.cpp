#include <algorithm>
#include <iostream>
#include <vector>

/*
    Leetcode 1046 Last Stone Weight
    You are given an array of integers stones where stones[i] is the weight of the ith stone.

    We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together.
    Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

    If x == y, both stones are destroyed, and
    If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
    At the end of the game, there is at most one stone left.

    Return the weight of the last remaining stone. If there are no stones left, return 0.

    Algorithm:
    Use a max heap.
*/

class Solution {
public:
    /**
     * @brief Get the last stone weight after the smashing simulation process detailed in description.
     * @param stones Vector of int representing weight of stones.
     * @returns Int weight of the last stone remaining.
     */
    int lastStoneWeight(std::vector<int>& stones) {
        // Heapifying existing vector over using a separate priority queue,
        // making the code space efficient.
        std::make_heap(stones.begin(), stones.end());

        while(stones.size() > 1) {
            // Heaviest stone.
            auto heaviest_stone = stones.front();
            std::pop_heap(stones.begin(), stones.end());
            stones.pop_back();

            // Second heaviest stone.
            auto second_heaviest_stone = stones.front();
            std::pop_heap(stones.begin(), stones.end());
            stones.pop_back();

            // Smashing destroys both.
            if (heaviest_stone == second_heaviest_stone) {
                continue;
            }

            // Unequal weight.
            heaviest_stone -= second_heaviest_stone;
            stones.push_back(heaviest_stone);

            // Use push_heap over make_heap to maintain heap property.
            std::push_heap(stones.begin(), stones.end());
        }

        // If one stone is left, return its weight; otherwise, return 0
        return stones.empty() ? 0 : stones.front();
    }
};