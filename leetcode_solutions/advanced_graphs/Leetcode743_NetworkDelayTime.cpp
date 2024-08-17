#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
/*
    Leetcode 743 Network Delay Time
    You are given a network of n nodes, labeled from 1 to n. You are also given times,
    a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node,
    vi is the target node, and wi is the time it takes for a signal to travel from source to target.

    We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal.
    If it is impossible for all the n nodes to receive the signal, return -1.

    Algorithm:
    Dijkstra's algorithm.

    Initialization.
    Store the graph in a hashmap mapping from int to a pair using the times vector.
    A vector with time to reach values for each node initialized as inf.
    A priority queue Q with start node added to it with time = 0
    (A set of visited nodes not needed because Dijsktra's may visit the same node again if a shorter path is found.
    However, the algo will not reconsider the parent again because doing so will up the distance to the parent.)


    while (Q not empty) {
        v = Q.pop()
        if v.time_to_reach >= v.current_time:
            (This mean v was added to the Q following a longer path
            Considering it again would mean all the nodes downstream may get visited twice)
            continue;

        // v has been reached by the shortest path till now.
        for n in v.neighbors:
            time_n = v.time + edge_time;

            if time_n < n.time:
                n.time = time_n
                Add (time_n, n) to Q.
    }
    time to explore = max of all times.
    time to explore == inf : return -1.
    return time_to_explore

*/

class Solution {
public:
    /**
     * @brief Calculate minimum time for signal to reach all the nodes in a network.
     * @param times Vector of vectors (source node, target node, time).
     * Each such vector represents an edge.
     * @param n Int number of nodes numbered from 1.
     * @param k Int index denoting the node from where signal is sent.
     * @returns Int minimum time for signal to reach all nodes in network.
     */
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {

        // Initialize all datastructures relevant to the algorithm.
        initialize_dijkstra_algorithm(times, n, k);

        while (!priority_queue.empty()) {
            auto current_node = priority_queue.top();
            priority_queue.pop();

            // If current node has previous recorded smaller time.
            if (current_node.first > smallest_time_to_reach_node[current_node.second]) {
                continue;
            }
            // Update smallest time for current.
            smallest_time_to_reach_node[current_node.second] = current_node.first;

            // Neighbors
            for (const auto & neighbor : network_graph[current_node.second]) {
                int time_to_neighbor = current_node.first + neighbor.first;

                // If this is smaller than recorded time to neighbor from k.
                if (time_to_neighbor < smallest_time_to_reach_node[neighbor.second]) {
                    auto neighbor_pair = std::make_pair(time_to_neighbor, neighbor.second);
                    priority_queue.push(neighbor_pair);

                    // Update time to reach neighbor.
                    smallest_time_to_reach_node[neighbor.second] = time_to_neighbor;
                }
            }
        }

        auto time_last_node_iterator =
            std::max_element(smallest_time_to_reach_node.begin() + 1, smallest_time_to_reach_node.end());

        int network_delay_time = *time_last_node_iterator;

        if (network_delay_time == std::numeric_limits<int>::max()) {
            return -1;
        }

        return network_delay_time;
    }

private:
    /**
     * @brief Populate network graph hashmap, current fastest times and adding first
     * node to priority queue.
     * @param n Int number of nodes numbered from 1.
     * @param k Int index denoting the node from where signal is sent.
     */
    void initialize_dijkstra_algorithm(std::vector<std::vector<int>>& times, int n, int k) {
        // Initialize times to reach each node.
        smallest_time_to_reach_node.resize(n + 1, std::numeric_limits<int>::max());

        priority_queue.push(std::make_pair(0, k));

        // Build graph.
        for (const auto & edge : times) {
            network_graph[edge[0]].emplace_back(std::make_pair(edge[2], edge[1]));
        }
    }

    std::vector<int> smallest_time_to_reach_node;

    // Priority queue for Dijsktra's algorithm.
    // 1st element is time to reach node and 2nd element is node index in a pair.
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> priority_queue;

    // Hashmap to store graph.
    // A neighbor pair has 1st element as time to traverse edge and 2nd as the index.
    std::unordered_map<int, std::vector<std::pair<int, int>>> network_graph;
};