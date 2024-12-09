# include<vector>
class Solution {
public:
    /**
     * @brief Find redundant connection in a tree using Union Find.
     *
     * @param edges Vector of vector of ints representing n edges.
     * @return std::vector<int> Redundant Edge.
     */
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        // Initialize Union find array with each node as its own parent
        parent_array.resize(edges.size() + 1);
        for (int i = 0; i <= edges.size(); i++) {
            parent_array[i] = i;  // Each node is its own parent initially
        }

        // Initialize rank array
        rank_vector.resize(edges.size() + 1, 1);

        std::vector<int> redundant_edge;
        for (const auto & edge : edges) {
            if (!union_method(edge[0], edge[1])) {
                redundant_edge = edge;
                break;
            }
        }

        return redundant_edge;
    }

private:
    std::vector<int> parent_array;
    std::vector<int> rank_vector;

    /**
     * @brief Union method of union find algorithm.
     *
     * @param node1 Int node 1
     * @param node2 Int node 2
     * @return true If the nodes can be merged into one group.
     * @return false False if the nodes are already part of the same group and cannot be merged.
     */
    bool union_method(int node1, int node2) {
        auto parent_1 = find_method(node1);
        auto parent_2 = find_method(node2);

        if (parent_1 == parent_2) {
            return false;  // Found cycle
        }

        // Union by rank
        if (rank_vector[parent_1] > rank_vector[parent_2]) {
            parent_array[parent_2] = parent_1;
            rank_vector[parent_1] += rank_vector[parent_2];
        }
        else if (rank_vector[parent_2] > rank_vector[parent_1]) {
            parent_array[parent_1] = parent_2;
            rank_vector[parent_2] += rank_vector[parent_1];
        }
        else {
            // When ranks are equal, choose parent_1 as parent and increment its rank
            parent_array[parent_2] = parent_1;
            rank_vector[parent_1]++;
        }
        return true;
    }

    /**
     * @brief Find the root of the node.
     *
     * @param node
     * @return int Integer root of the group to which the node belongs.
     */
    int find_method(int node) {
        // Path compression: Make each node point directly to the root
        if (parent_array[node] != node) {
            parent_array[node] = find_method(parent_array[node]);
        }
        return parent_array[node];
    }
};