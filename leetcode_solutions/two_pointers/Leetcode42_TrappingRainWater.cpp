#include <iostream>
#include <vector>

/**
 * @brief Given n non-negative integers representing an elevation map where
 * the width of each bar is 1, compute how much water it can trap after
 * raining.
 *
 * Key: Water trapped at a particular index is min(max height left, max height right).
 * You can ONLY know water at that location if you know the min wall height around it.
 * In the two pointer algorithm then, do i++ or j-- ONLY if for indices <= i or indices >= j
 * you know the wall height with certainty.
 *
 * Steps:
 * 1. i = 0; j = n; maxl = ith, maxr = jth; result = 0
 * 2. while (i < j)
 *  a. if maxl < maxr
 *      i++; add (maxl - ith) to result; update maxl
 *  b. if maxl >  maxr
 *      j--; add (maxr - jth) to result; update maxr.
 *
 * @param height Array of heights
 * @result Water trapped as integer
 */

class Solution {
public:
    int trap(std::vector<int>& height) {
        // initialize pointers and result.
        int i = 0, j = height.size() - 1, result = 0;
        // maxl and maxr as current heights.
        int maxl = height[i];
        int maxr = height[j];

        // O(n) time complexity
        while (i < j){
            if (maxl <= maxr){
                // Move i since maxl is lesser.
                i++;
                // Exact water can be computed for ith, because we know its
                // min height; can't be done for jth at this time.
                auto water_content = maxl - height[i];
                // Add water if positive.
                if (water_content > 0){
                    result += water_content;
                }
                // Update maxl.
                maxl = std::max(maxl, height[i]);
            } else {
                // Move j since maxr is lesser.
                j--;
                // Exact water can be computed for jth, because we know its
                // min height; can't be done for ith at this time.
                auto water_content = maxr - height[j];
                // Add water if positive
                if (water_content > 0){
                    result += water_content;
                }
                // Update maxr.
                maxr = std::max(maxr, height[j]);
            }
        }
        return result;
    }
};

/*
An easier way to handle this is with O(n) time and O(n) space.

First iterate left to right and store max left heights for all positions.
Then iterate right to left and store max right heights for all positions.
Find min height for all. ( Can be done during second for loop.)

Then do another for loop and calculate water content based off min height.
*/