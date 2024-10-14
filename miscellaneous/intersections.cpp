#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

/*
Problem Description:
---------------------
You are given n segments, where each segment i is described by two integers: startsAt[i] and endsAt[i].
The segment covers all points between startsAt[i] and endsAt[i] inclusive on a number line.

Task:
-----
For each segment i, count how many other segments it intersects with. Two segments intersect if
they share at least one common point on the number line.

Function Signature:
-------------------
std::vector<int> countIntersections(const std::vector<int>& startsAt, const std::vector<int>& endsAt);

Input:
------
- startsAt: A vector of integers representing the starting points of n segments.
- endsAt: A vector of integers representing the ending points of n segments.

Output:
-------
- A vector of integers, where the i-th element represents the number of segments that intersect
  with the i-th segment.

Constraints:
------------
- 1 ≤ n ≤ 10^5
- 1 ≤ startsAt[i] ≤ endsAt[i] ≤ 10^9

Example:
--------
Input:
startsAt = {1, 3}
endsAt = {4, 5}

Output:
[1, 1]

Explanation:
------------
The 1st segment [1, 4] intersects with the 2nd segment [3, 5] at points 3 and 4. Both segments
have one intersection, so the answer is [1, 1].
*/

// Custom comparator for min heap based on the first element of the tuple
struct Event {
    // Position or index of the event.
    int position;

    // Segment to which the event belongs to.
    int segment;

    // 1 or -1, 1 for start and -1 for end.
    int event_type;

    // Overload operator< to compare events based on segment
    bool operator<(const Event& other) const {
        if (position == other.position)
            // IMPORTANT
            // Start event is given a higher priority than end event.
            // Thus in the priority queue, start will be processed before end for the same position, making sure that the
            // the index where one segment ends another starts is counted as an intersection.
            return event_type < other.event_type;
        return position > other.position;
    }
};

/**
 * @brief Counts the number of intersections for each segment.
 *
 * This function processes a list of segments defined by their start and end points
 * and calculates how many other segments each segment intersects with.
 *
 * @param startsAt A vector of integers representing the start points of the segments.
 * @param endsAt A vector of integers representing the end points of the segments.
 * @returns A vector of integers where each element represents the number of intersections
 *          for the corresponding segment.
 */
std::vector<int> countIntersections(const std::vector<int>& startsAt, const std::vector<int>& endsAt) {
    int n = startsAt.size();

    // Store the number of intersections.
    auto intersections = std::vector<int>(n, 0);

    // Priority Queue storing start and end events in chronological order.
    // Needs the < operator defined.
    std::priority_queue<Event> event_list;

    // Populate event list.
    for (int i = 0; i < n; i++) {
        Event start_event;
        start_event.position = startsAt[i];
        start_event.segment = i;
        start_event.event_type = 1;
        event_list.push(start_event);
    }

    for (int i = 0; i < n; i++) {
        Event end_event;
        end_event.position = endsAt[i];
        end_event.segment = i;
        end_event.event_type = -1;
        event_list.push(end_event);
    }

    // Set to store active segments indices.
    std::unordered_set<int> active_segments;

    while(!event_list.empty()) {

        auto event = event_list.top();
        event_list.pop();

        // If the event is end.
        if (event.event_type == -1) {
            // Remove corresponding segment.
            active_segments.erase(event.segment);
            continue;
        }

        // Number of intersections is equal to the number of active segments.
        intersections[event.segment] = active_segments.size();

        // Iterate through the active segments and increment their intersections.
        for (auto & event_index : active_segments) {
            intersections[event_index] ++;
        }

        // Add new segment to active segments.
        active_segments.insert(event.segment);
    }

    return intersections;
}

int main() {
    // Test Case 1: Basic example with 2 segments
    std::cout << "Test Case 1:" << std::endl;
    std::vector<int> startsAt1 = {1, 3};
    std::vector<int> endsAt1 = {4, 5};
    std::vector<int> result1 = countIntersections(startsAt1, endsAt1);
    for (int i : result1) std::cout << i << " "; // Expected output: 1 1
    std::cout << std::endl << std::endl;

    // Test Case 2: Overlapping segments
    std::cout << "Test Case 2:" << std::endl;
    std::vector<int> startsAt2 = {1, 2, 3};
    std::vector<int> endsAt2 = {4, 5, 6};
    std::vector<int> result2 = countIntersections(startsAt2, endsAt2);
    for (int i : result2) std::cout << i << " "; // Expected output: 2 2 2
    std::cout << std::endl << std::endl;

    // Test Case 3: Segments that do not overlap at all
    std::cout << "Test Case 3:" << std::endl;
    std::vector<int> startsAt3 = {1, 10, 20};
    std::vector<int> endsAt3 = {5, 15, 25};
    std::vector<int> result3 = countIntersections(startsAt3, endsAt3);
    for (int i : result3) std::cout << i << " "; // Expected output: 0 0 0
    std::cout << std::endl << std::endl;

    // Test Case 4: Nested segments
    std::cout << "Test Case 4:" << std::endl;
    std::vector<int> startsAt4 = {1, 2, 3};
    std::vector<int> endsAt4 = {6, 5, 4};
    std::vector<int> result4 = countIntersections(startsAt4, endsAt4);
    for (int i : result4) std::cout << i << " "; // Expected output: 2 2 2
    std::cout << std::endl << std::endl;

    // Test Case 5: One large segment covering smaller ones
    std::cout << "Test Case 5:" << std::endl;
    std::vector<int> startsAt5 = {1, 2, 3};
    std::vector<int> endsAt5 = {10, 4, 5};
    std::vector<int> result5 = countIntersections(startsAt5, endsAt5);
    for (int i : result5) std::cout << i << " "; // Expected output: 2 2 2
    std::cout << std::endl << std::endl;

    // Test Case 6: Overlapping at single points
    std::cout << "Test Case 6:" << std::endl;
    std::vector<int> startsAt6 = {1, 2, 3, 4};
    std::vector<int> endsAt6 = {2, 3, 4, 5};
    std::vector<int> result6 = countIntersections(startsAt6, endsAt6);
    for (int i : result6) std::cout << i << " "; // Expected output: 1 2 2 1
    std::cout << std::endl << std::endl;

    // Test Case 7: Single segment
    std::cout << "Test Case 7:" << std::endl;
    std::vector<int> startsAt7 = {1};
    std::vector<int> endsAt7 = {5};
    std::vector<int> result7 = countIntersections(startsAt7, endsAt7);
    for (int i : result7) std::cout << i << " "; // Expected output: 0
    std::cout << std::endl << std::endl;

    // Test Case 8: All segments have the same start and end points
    std::cout << "Test Case 8:" << std::endl;
    std::vector<int> startsAt8 = {1, 1, 1};
    std::vector<int> endsAt8 = {5, 5, 5};
    std::vector<int> result8 = countIntersections(startsAt8, endsAt8);
    for (int i : result8) std::cout << i << " "; // Expected output: 2 2 2
    std::cout << std::endl << std::endl;

    // Test Case 9: Large segments
    std::cout << "Test Case 9:" << std::endl;
    std::vector<int> startsAt9 = {1, 1000000};
    std::vector<int> endsAt9 = {500000, 1000000};
    std::vector<int> result9 = countIntersections(startsAt9, endsAt9);
    for (int i : result9) std::cout << i << " "; // Expected output: 0 0
    std::cout << std::endl << std::endl;

    // Test Case 10: Edge case, smallest possible segments
    std::cout << "Test Case 10:" << std::endl;
    std::vector<int> startsAt10 = {1, 2, 3};
    std::vector<int> endsAt10 = {1, 2, 3};
    std::vector<int> result10 = countIntersections(startsAt10, endsAt10);
    for (int i : result10) std::cout << i << " "; // Expected output: 0 0 0
    std::cout << std::endl << std::endl;

    return 0;
}

// // Brute Force Solution.
// std::vector<int> countIntersections(const std::vector<int>& startsAt, const std::vector<int>& endsAt) {
//     int n = startsAt.size();

//     // Store the number of intersections.
//     auto intersections = std::vector<int>(n, 0);

//     for (int i = 0; i < n; i++) {
//         for (int j = i + 1; j < n; j++) {
//             // Check for intersection between the ith and jth segment.
//             if (endsAt[i] < startsAt[j] || endsAt[j] < startsAt[i]) {
//                 // No intersection.
//                 continue;
//             }
//             // Incremenet intersection counts.
//             intersections[i] ++;
//             intersections[j] ++;
//         }
//     }
//     return intersections;
// }