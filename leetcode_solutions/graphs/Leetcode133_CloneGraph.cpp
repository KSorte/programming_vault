#include <queue>
#include <vector>
#include <unordered_map>

/*
    Leetcode 133 Clone Graph
    Given a reference of a node in a connected undirected graph.
    Return a deep copy (clone) of the graph.
    Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

    Approach:
    Implement BFS and simultaneously replicate the graph.

    Considerations:
    Initially, a set of visited nodes from old graph is used. But this approach assumed that graph is unidirectional like a
    tree. In a tree, once you come upon a new neighbor in the old graph, you create its new counterpart, which is added to the new queue.
    This approach assumes that clone nodes popped from the queue won't ever be needed again, because that is how tree traversal works.

    But if a bi-directional graph is considered, a node encountered later on might be connected to a node that was encountered long ago in
    the BFS. In this case, unless you have a map mapping from the node of old graph to that of new graph (the new node counterpart exists), you
    cannot access it. The problem that needs to be tackled is that you need to form a connection with an existing node.
    A mapping from old to new nodes is the only way to solve it.
*/

// Definition for a Node.
class Node {
public:
    // Value associated with the node.
    int val;
    // Vector of neighbors.
    std::vector<Node*> neighbors;

    /**
     * @brief Constructor
     */
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }

    /**
     * @brief Constructor.
     * @param _val Value for the node.
    */
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }

    /**
     * @brief Constructor
     * @param _val Value for the node.
     * @param _neighbors Vector of neighbor nodes.
     */
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// Solution below works for unidirectional graph.
class Solution {
public:
    /**
     * @brief Clones the graph with new nodes and new pointers.
     * @param node Node node in a graph.
     * @returns The corresponding node from the cloned graph.
     */
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        queue_bfs.push(node);
        map_old_to_clone[node] = new Node(node->val);

        // Breadth first search.
        while (!queue_bfs.empty()) {
            auto node_front = queue_bfs.front();
            queue_bfs.pop();

            for (auto & neighbor : node_front->neighbors) {
                auto iterator_visited_nodes = map_old_to_clone.find(neighbor);

                // If neighbor not visited before.
                if (iterator_visited_nodes == map_old_to_clone.end()) {
                    // Make a copy.
                    map_old_to_clone[neighbor] = new Node(neighbor->val);

                    // Push neighbor in queue.
                    queue_bfs.push(neighbor);
                }

                map_old_to_clone[node_front]->neighbors.push_back(map_old_to_clone[neighbor]);
            }
        }
        return map_old_to_clone[node];
    }

private:
    // Map from old to the clone.
    std::unordered_map<Node*, Node*> map_old_to_clone;

    // Queue for breadth first search.
    std::queue<Node*> queue_bfs;
};

// Solution assuming that the graph is unidirectional.
//     Node* cloneGraph(Node* node) {
//         if (node == nullptr) {
//             return nullptr;
//         }

//         std::queue<Node*> queue_bfs_old_graph;
//         std::queue<Node*> queue_bfs_clone_graph;
//         std::unordered_set<Node*> nodes_visited_old_graph;

//         Node* clone_node = new Node(node->val);

//         queue_bfs_old_graph.push(node);
//         queue_bfs_clone_graph.push(clone_node);

//         // BFS Search.
//         while (queue_bfs_old_graph.size() > 0) {
//             auto node = queue_bfs_old_graph.front();
//             nodes_visited_old_graph.insert(node);

//             auto clone_node = queue_bfs_clone_graph.front();

//             queue_bfs_old_graph.pop();
//             queue_bfs_clone_graph.pop();

//             for (auto & neighbor : node->neighbors) {
//                 auto iterator_visited_nodes = nodes_visited_old_graph.find(neighbor);

//                 if (iterator_visited_nodes != nodes_visited_old_graph.end()) {
//                     // Neighbor visited before.
//                     continue;
//                 }

//                 // Copy neighbor and add to node neighbor list.
//                 Node* clone_neighbor = new Node(neighbor->val);
//                 clone_node->neighbors.push_back(clone_neighbor);
//                 clone_neighbor->neighbors.push_back(clone_node);

//                 // Add to respective queues.
//                 queue_bfs_old_graph.push(neighbor);
//                 queue_bfs_clone_graph.push(clone_neighbor);
//             }
//         }
//         return clone_node;
//     }