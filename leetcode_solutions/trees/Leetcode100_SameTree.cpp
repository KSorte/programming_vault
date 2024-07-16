#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
/*
Leetcode 100 Same Tree
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Method1:
BFS algorithm that simultaneously runs on both trees. Returns true by default.
Returns false as soon as inequality between values encountered.
But this method suffers from handling nullptrs and all the edge cases that can happen there.
Edge case handling with the classic BFS is a nightmare.

Method2:
Check if the current node in p an q is equal.
if it is, then recursively check the equality of the subtrees.
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
     * @brief Determines whether the two binary trees are the same.
     * @param p TreeNode* pointer pointing to root node of first tree.
     * @param q TreeNode* pointer pointing to root node of second tree.
     * @returns Boolean indicating whether the two binary trees are the same.
     */
    bool isSameTree(TreeNode* p, TreeNode* q) {

        if (p == NULL && q == NULL) {
            // If both are nullptrs, return true.
            return true;
        }
        if (p == NULL || q == NULL) {
            // If one of them is null, return false.
            return false;
        }
        if (p->val != q->val) {
            // If values are unequal, return false.
            return false;
        }

        // All subtrees should be equal.
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

int main() {
    Solution same_tree;
    // Test case 1
    TreeNode* tree1 = nullptr;
    TreeNode* tree2 = nullptr;
    std::cout<<"Result 1: "<<same_tree.isSameTree(tree1, tree2)<<std::endl;


    // Test case 2
    tree1 = new TreeNode(1);
    tree2 = new TreeNode(1);
    // tree2 = nullptr;
    std::cout<<"Result 2: "<<same_tree.isSameTree(tree1, tree2)<<std::endl;

    // Create p and q like [1, null, 1]
    TreeNode* p = new TreeNode(1);
    p->right = new TreeNode(1);

    TreeNode* q = new TreeNode(1);
    q->right = new TreeNode(1);
    bool result = same_tree.isSameTree(p, q);
    std::cout<<"Result 3: "<<result<<std::endl;

}