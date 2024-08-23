#include <queue>
#include <unordered_map>
#include <vector>
/*
    Leetcode 323 Number of Connected Components in Undirected Graph
    You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates
    that there is an edge between ai and bi in the graph.

    Return the number of connected components in the graph.

    Algorithm:
    Use BFS and approach very similar to Leetcode 200 Number of Islands. Refer 200.
    You are basically finding the number of islands.

    However, a much better way of solving this is Union Find. Implemented elsewhere.
*/

class Solution {
public:
    /**
     * @brief Calculate number of connected components in an undirected graph, where nodes
     * are number from 0 to n - 1.
     * @param n Int n denoting number of nodes.
     * @param edges Vector of vector of ints representing edges.
     * @returns Int number of connected components.
     */
    int countComponents(int n, std::vector<std::vector<int>>& edges) {

        // Create graph.
        for (const auto & edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        visited.resize(n);

        for (int i = 0; i < n; i++) {
            breadth_first_search(i);
        }
        return num_components;
    }

private:
    // Hash map to store graph.
    std::unordered_map<int, std::vector<int>> graph;

    // Number of components.
    int num_components;

    // Vector to mark visited nodes.
    std::vector<bool> visited;

    /**
     * @brief BFS to scan through all nodes to get the number of connected nodes.
     * @param node Int node.
     */
    void breadth_first_search(int node){
        if (visited[node]) {
            // Node visited.
            return;
        }

        std::queue<int> queue;

        queue.push(node);

        while(!queue.empty()) {
            auto current_node = queue.front();
            queue.pop();

            for (const auto & neighbor : graph[current_node]) {
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                }
            }

            visited[current_node] = true;
        }

        num_components ++;
     }
};