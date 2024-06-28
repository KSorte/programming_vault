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
Increment depth.

This is the same procedure as Leetcode 102 Binary Tree Level Order Travsersal.
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
     * @brief Return the maximum depth of the binary tree.
     * @param root Root of the binary tree.
     * @returns Integer depth of the binary tree.
     */
    int maxDepth(TreeNode* root) {
        // Initialize queue for BFS
        // This is a queue of pointers to the class TreeNode
        std::queue<TreeNode*> queue;

        // Initialize depth to 0.
        int depth = 0;

        if (!root) {return depth;}

        // add root to queue and increment depth.
        queue.push(root); depth ++;

        // Iterate until the queue size becomes zero.
        while(queue.size() > 0) {
            // Get length of queue.
            int length_of_current_level = queue.size();

            // Currently queue contains elements of a particular level; pop them in a loop.
            for (int i = 0; i < length_of_current_level; i++) {
                // Get first element and pop it.
                auto first_element_queue = queue.front(); queue.pop();

                // Add left and right of first element to new level and queue.
                if (first_element_queue->left) {
                    queue.push(first_element_queue->left);
                }

                if (first_element_queue->right) {
                    queue.push(first_element_queue->right);
                }
            } // One level traversed, end of for loop.

            // If queue size > 0, then next level exists, increment depth.
            if (queue.size() > 0) {depth ++;}
        }
        return depth;;
    }

    // Using RECURSION

    // int maxDepth(TreeNode* root) {
    //     if (root == NULL) {
    //         return 0;
    //     }
    //     return 1 + max(maxDepth(root->left), maxDepth(root->right));
    // }
};