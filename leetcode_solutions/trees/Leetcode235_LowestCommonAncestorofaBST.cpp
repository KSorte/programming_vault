/*
    Leetcode 235 Lowest Common Ancestor of a Binary Search Tree
    Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

    According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes
    p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

    Algorithm:

    First assumption:
        The tree is valid and p, q both exist.

    based on the values first determine if the p and q exist under left or right.
    If under left subtree, then left WONT be a nullptr. Similarly with right.
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
     * @brief Returns the pointer to the lower common ancestor of two nodes in BST.
     * @param p TreeNode* pointer to a node in BST.
     * @param q TreeNode* pointer to a node in BST.
     * @returns TreeNode* pointer to the lowest common ancestor.
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (p->val > root->val && q->val > root->val) {
            // Both exists definitely under right subtree,
            // And right child is NOT a nullptr.
            return lowestCommonAncestor(root->right, p, q);
        }

        if (p->val < root->val && q->val < root->val) {
            // Both exists definitely under left subtree,
            // And left child is NOT a nullptr.
            return lowestCommonAncestor(root->left, p, q);
        }

        /** This handles all the other cases.
         * P and Q split between left and right child.
         * Either p or q equal the root in value, then root becomes the correct answer.
         */
        return root;
    }
};