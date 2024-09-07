#include <limits>
/*
    Leetcode 1448 Cound Good Nodes in Binary Tree
    Given a binary tree root, a node X in the tree is named good if in the path from root to X
    there are no nodes with a value greater than X.

    Return the number of good nodes in the binary tree.

    Algo:
    DFS.
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
     * @brief Find the number of good nodes in a binary tree.
     * @param root TreeNode* root of the BT.
     * @returns Int number of good nodes in the tree.
     */
    int goodNodes(TreeNode* root) {
       return depth_first_search(root, std::numeric_limits<int>::min());
    }

private:
    /**
     * @brief DFS to traverse the tree.
     * @param root TreeNode* subnode.
     * @param curr_max Int current maximum value on the path.
     * @returns Int number of good nodes in the subtree.
     */
    int depth_first_search(TreeNode* root, int curr_max) {
        if (!root) {
            return 0;
        }

        int count = 0;
        if (curr_max <= root->val) {
            // Node is good.
            count ++;
            curr_max = root->val;
        }

        count += depth_first_search(root->left, curr_max);
        count += depth_first_search(root->right, curr_max);

        return count;
    }
};