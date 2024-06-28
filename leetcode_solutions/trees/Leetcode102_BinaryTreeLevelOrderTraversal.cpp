#include <iostream>
#include <queue>
#include <vector>

/*

Leetcode 102 Binary Tree Level Order Traversal
Given the root of a binary tree, return the level order traversal of its nodes' values.
(i.e., from left to right, level by level).

The idea is to modify BFS slightly.
In original BFS, we pop one element of the queue at a time
and add its neighbors to the queue.

In this modified version, we pop all the elements of a particular level at once.

In this manner, at the start of BFS while loop, the queue contains all elements of a particular level.
Then you pop all of these and add their neighbors(next level elements) to the queue.

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
     * @brief Return the level order traversal of a binary tree using modified BFS.
     * @param root Root of the binary tree to be traversed.
     * @returns Vector of integer vector where each vector is a level of the binary tree.
     */
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        // Initialize queue for BFS
        // This is a queue of pointers to the class TreeNode
        std::queue<TreeNode*> queue;
        // Initialize level order traversal
        std::vector<std::vector<int>> level_order_traversal;

        if (!root) {
            return level_order_traversal;
        }

        // add root to queue and level order traversal
        queue.push(root);
        level_order_traversal.push_back({root->val});

        // Iterate until the queue size becomes zero.
        while(queue.size() > 0) {
            // Get length of queue.
            int length_of_current_level = queue.size();

            // Initialize vector to store nodes from next level
            std::vector<int> next_level;

            // Currently queue contains elements of a particular level; pop them in a loop.
            for (int i = 0; i < length_of_current_level; i++) {
                // Get first element and pop it.
                auto first_element_queue = queue.front(); queue.pop();

                // Add left and right of first element to new level and queue.
                if (first_element_queue->left) {
                    next_level.push_back(first_element_queue->left->val);
                    queue.push(first_element_queue->left);
                }

                if (first_element_queue->right) {
                    next_level.push_back(first_element_queue->right->val);
                    queue.push(first_element_queue->right);
                }
            } // One level traversed, end of for loop.

            // Add next level to level order traversal, if it of non-zero size.
            if (next_level.size() > 0) {
                level_order_traversal.push_back(next_level);
            }
        }
        return level_order_traversal;
    }
};