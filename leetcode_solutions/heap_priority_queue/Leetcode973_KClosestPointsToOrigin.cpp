#include <vector>
#include <queue>
#include <iostream>
/*
    Leetcode 973 K Closest Points to Origin
    Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k,
    return the k closest points to the origin (0, 0).

    The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

    You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

    Algorithm:
    Use min heap priority queue. Optimize well.

*/

class Solution {
public:
    /**
     * @brief Find the k closest point to origin.
     * @param points Vector of vector of int representing points.
     * @param k Int k number of points to find.
     * @returns Vector of vector of ints representing the k closest points to origin.
     */
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Min Heap.
        std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>> priority_queue;

        // Add to min heap.
        for (int i = 0; i < points.size(); i ++) {
            double distance = points[i][0]*points[i][0] + points[i][1]*points[i][1];
            // priority_queue.push({distance, i});
            priority_queue.emplace(distance, i);  // Use emplace to construct pair in place inside the pq.

            // One way is to maintain a queue of size k by continually checking if the size is k.
            // The logic is to make subsequent additions cheaper, since addition to a priority queue is O(logn)
            // HOWEVER, for large n (say all between 256 and 512), logn value remains mostly the same, but the addition
            // of an if is an O(n) computation expense, which significantly slows down the code.
        }

        // Result vector.
        std::vector<std::vector<int>> k_closest_points;

        // Pop from priority_queue.
        for (int i = 0; i < k; i++) {
            auto point = priority_queue.top();
            priority_queue.pop();
            // No need of emplace back because object is already created.
            k_closest_points.push_back(points[point.second]);
        }

        return k_closest_points;
    }
};