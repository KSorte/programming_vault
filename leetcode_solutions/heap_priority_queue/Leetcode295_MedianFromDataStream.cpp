#include <iostream>
#include <queue>
#include <vector>

/*
    Leetcode 295 Median From Data Stream
    The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value,
    and the median is the mean of the two middle values.

    For example, for arr = [2,3,4], the median is 3.
    For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
    Implement the MedianFinder class:

    MedianFinder() initializes the MedianFinder object.
    void addNum(int num) adds the integer num from the data stream to the data structure.
    double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.

    Algorithm:
    Two heaps, min heap for holding upper half of the data stream;
    Max heap for holding the lower half and the median if the elements are odd.

    Add operation (num)
    Following cases exist:
    - num > min heap top
        Add number to min heap (greater heap)
    - num < max heap top
        Add number to max heap (smaller heap)
    - max heap top <= num <= min heap top
        Check distance from both tops.
        Add to heap for which the distance is smaller.

        if distance is equal, add to the heap in such a manner that the
        lengths are equal.

    after addition, check the lengths of both heaps. If the difference >=2
    add number from smaller LENGTH heap the greater LENGTH heap.

    find median operation()
    if lengths equal, get the average of tops.
    if lengths unequal, get the top of the larger LENGTH heap.

*/

class MedianFinder {
public:
    /**
     * @brief Constructor.
     * Adds the input limits to max heap and min heap.
     */
    MedianFinder() {
        max_heap.push(MIN_INPUT_IN_STREAM);
        min_heap.push(MAX_INPUT_IN_STREAM);

    }

    /**
     * @brief Adds number to the datastructure.
     * Adds it to either min heap or max heap depending on various conditions.
     * @param num Int number to add to data structure.
     */
    void addNum(int num) {
        if (num > min_heap.top()) {
            // O(logn)
            min_heap.push(num);
        } else if (num < max_heap.top()) {
            // O(logn)
            max_heap.push(num);
        } else {
            int distance_to_min_heap = min_heap.top() - num;
            int distance_to_max_heap = num - max_heap.top();

            if (distance_to_max_heap >= distance_to_min_heap) {
                // O(logn)
                min_heap.push(num);

            } else {
                // O(logn)
                max_heap.push(num);

            }
        }

        // Check sizes of both heaps.
        if (min_heap.size() > max_heap.size()) {
            if (min_heap.size() - max_heap.size() >= 2) {
                // O(logn)
                max_heap.push(min_heap.top());
                // O(logn)
                min_heap.pop();
                return;
            }
        }

        if (max_heap.size() > min_heap.size()) {
            if (max_heap.size() - min_heap.size() >= 2) {
                // O(logn)
                min_heap.push(max_heap.top());
                // O(logn)
                max_heap.pop();
                return;
            }
        }

        // Doing it in one if. Makes the code slightly unreadable.
        // if (std::abs(static_cast<int>(min_heap.size()) - static_cast<int>(max_heap.size())) >= 2) {
        //     if (min_heap.size() > max_heap.size()) {
        //         max_heap.push(min_heap.top());
        //         min_heap.pop();
        //     } else {
        //         min_heap.push(max_heap.top());
        //         max_heap.pop();
        //     }
        //     return;
        // }
        return;
    }

    /**
     * @brief Find median of the data stream stored in data structure.
     * @returns Double median of the data stream.
     */
    double findMedian() {
        double median;
        if (max_heap.size() == min_heap.size()) {
            median = (max_heap.top() + min_heap.top())/2.0;
        } else if (max_heap.size() > min_heap.size()) {
            median = max_heap.top();
        } else {
            median = min_heap.top();
        }
        return median;
    }

private:
    // Maximum possible input.
    static constexpr int MAX_INPUT_IN_STREAM = 1e5;

    // Minimum possible input.
    static constexpr int MIN_INPUT_IN_STREAM = -1e5;

    // Max heap to store the lower half of the data stream.
    std::priority_queue<int> max_heap;

    // Min heap to store the upper half of the data stream.
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

};