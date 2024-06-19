#include <iostream>
#include <vector>
/*
    Leetcode 84 Largest Rectangle in Histogram.
    https://medium.com/algorithms-digest/largest-rectangle-in-histogram-234004ecd15a
    Given an array of integers heights representing the histogram's bar height where
    the width of each bar is 1, return the area of the largest rectangle in the histogram.

    Each rectangle height is limited by its smallest member.
    The brute force method is to iterate through all heights considering them to be the smallest
    for the iteration. Then, finding correspoding rectangle by finding smaller heights on the left
    and right respectively.
    This is O(n2) approach.

    Another method is:
    1. Find the previous smaller element and next smaller element for each height
    using O(n) approach.
    2. Once you have this information, iterating through heights and keeping track
    of the max rect area should work.

    This approach is O(n) time complexity and space complexity because you need to store the
    previous and next smaller heights for each height once.

*/

class Solution {
public:
    /**
     * @brief Computes the largest possible rectangle from the vector of
     * historgram heights.
     * @param heights Vector of historgram heights.
     * @returns Integar largest rectangle area.
     */
    int largestRectangleArea(std::vector<int>& heights) {

        // Size of heights array.
        int n = heights.size();

        // Each pair in this vector stores the limits of rectangle formed by keeping the index
        // i height as the smallest height.
        std::vector<std::pair<int, int>> rectangle_limits(n);

        // Initialize the left limit of the leftmost element as -1.
        rectangle_limits[0].first = -1;

        // Initialize the right limit of the rightmost element as n.
        rectangle_limits[n - 1].second = n;

        // Iterate over the heights array to get the previous
        // smaller index of each height.
        // O(n)
        for (int i = 1; i<n; i++){
            int prev_index = i - 1;

            while (heights[prev_index] >= heights[i]){
                // If the previous smaller element of previous index is -1,
                // it indicates it has no element smaller than it on the left.
                if (rectangle_limits[prev_index].first == -1){
                    prev_index = -1;
                    break;
                }

                // Assign the prev_index as the previous smaller element of the element
                // at 'prev_index'; we are back tracking to get the previous smaller element for i.
                prev_index = rectangle_limits[prev_index].first;
            }

            // Assign prev_index after back tracking to the ith element.
            rectangle_limits[i].first = prev_index;
        }

        // Iterate over the heights array to get the next
        // smaller index of each height; iterate from back.
        // O(n)
        for (int i = n - 2; i >= 0; i--){
            int next_index = i + 1;

            while (heights[next_index] >= heights[i]){
                // If the next smaller element of next index is n,
                // it indicates it has no element smaller than it on the right.
                if (rectangle_limits[next_index].second == n){
                    next_index = n;
                    break;
                }

                // Assign the next_index as the next smaller element of the element
                // at 'next_index'; we are back tracking to get the next smaller element for i.
                next_index = rectangle_limits[next_index].second;
            }

            // Assign next_index after back tracking to the ith element.
            rectangle_limits[i].second = next_index;
        }

        int max_rectangle_area = 0;
        // Find the max rectangle area using limits computed before.
        // O(n)
        for (int i = 0; i < n; i++){
            auto curr_rect =
                (rectangle_limits[i].second - rectangle_limits[i].first - 1)*heights[i];
            // If current rectangle is larger than max rectangle area, update the latter.
            max_rectangle_area = (curr_rect > max_rectangle_area) ? curr_rect : max_rectangle_area;
        }
    return max_rectangle_area;
    }
};

int main(){
    Solution sol;

    std::vector<int> input = {2,1,5,6,2,3};
    std::cout<<sol.largestRectangleArea(input);
}