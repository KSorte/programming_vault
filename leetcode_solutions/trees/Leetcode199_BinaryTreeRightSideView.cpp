#include <queue>
#include <vector>
/*
    Leetcode 199 Binary Tree Right Side View.
    Given the root of a binary tree, imagine yourself standing on the right side of it,
    return the values of the nodes you can see ordered from top to bottom.

    Algorithm:
         A special implementation of BFS level order traversal where at each level only the right most
         node is added to the queue.
         if right child is null, add the left child to the queue.

         OR recursive DFS that strictly goes through the right most elements.
*/

// Definition for a binary tree node.
struct TreeNode {
    // Tree Node value
    int val;

    // Pointer to left child.
    TreeNode *left;

    // Pointer to right child.
    TreeNode *right;

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     */
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     * @param x Integer for initializing val.
     */
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     * @param x Integer for initializing val.
     * @param *left Pointer to the left child of the node.
     * @param *right Pointer to the right child of the node.
     */
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /**
     * @brief Get the right side view of a binary tree.
     * @param root Treenode* pointer to the root of the binary tree.
     * @returns Vector of integers containing right side view of the tree.
     */
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> right_side_view;

        if (root == nullptr) {
            return right_side_view;
        }

        std::queue<TreeNode*> queue_bfs;
        queue_bfs.push(root);

        while (!queue_bfs.empty()) {
            // Get right most element on the level and add to result.
            auto right_most_node = queue_bfs.front();
            right_side_view.push_back(right_most_node->val);

            int current_level_size = queue_bfs.size();
            // Iterate through the entire tree level.
            for (int i = 0; i < current_level_size; i++) {
                auto current_node = queue_bfs.front();
                queue_bfs.pop();

                // Add elements right to left to queue.
                if (current_node->right != nullptr) {
                    queue_bfs.push(current_node->right);
                }

                if (current_node->left != nullptr) {
                    queue_bfs.push(current_node->left);
                }
            }
        }
        return right_side_view;
    }
};