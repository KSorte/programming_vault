#include<iostream>
#include<vector>
#include<algorithm>
/*
    Leetcode 708 Kth Largest Element in a Stream.
    Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order,
    not the kth distinct element.

    Implement KthLargest class:

    KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers nums.
    int add(int val) Appends the integer val to the stream and returns the element representing the kth largest element in the stream.

    Algorithm:
    Use a min Heap of size K.

    KthLargest:
    vector.make_heap()
    if heap size > k:
        pop heap until heap size is k.

    int add (val):
        heap_pop()  // remove minimum
        vector.pushback(val);  //
        heapify
        peek
*/

class KthLargest {
public:
    /**
     * @brief Constructor for KthLargest class.
     * Initializes the vector as a min_heap of size k using heap methods.
     * @param k Integer denoting k for getting kth largest element.
     * @param nums Vector of ints to convert to min_heap.
     */
    KthLargest(int k, std::vector<int>& nums) : k(k), min_heap(nums){
        std::make_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
        while (min_heap.size() > k) {
            // Sends top most element to the end of the vector.
            std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
            min_heap.pop_back();
        }
    }

    /**
     * @brief Add a new integer to the array and get the kth largest element after addition.
     * @param val Int to add.
     * @returns Integer Kth largest element.
     */
    int add(int val) {
        // Add new val to min_heap vector
        min_heap.push_back(val);
        // Heapify.
        std::push_heap(min_heap.begin(), min_heap.end(), std::greater<int>());

        if (min_heap.size() == k + 1) {
            // Remove top most element.
            std::pop_heap(min_heap.begin(), min_heap.end(), std::greater<int>());
            min_heap.pop_back();
        }

        return min_heap.front();
    }

private:
    int k;
    std::vector<int> min_heap;
};

// Using Priority Queue.

// class KthLargest {
// public:
//     KthLargest(int k, vector<int>& nums) {
//         this->k = k;
//         for (int i = 0; i < nums.size(); i++) {
//             pq.push(nums[i]);
//         }
//         while (pq.size() > this->k) {
//             pq.pop();
//         }
//     }
//     int add(int val) {
//         pq.push(val);
//         if (pq.size() > k) {
//             pq.pop();
//         }
//         return pq.top();
//     }
// private:
//     int k;
//     priority_queue<int, vector<int>, greater<int>> pq;
// };
