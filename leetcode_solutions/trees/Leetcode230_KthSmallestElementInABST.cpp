/*
    Leetcode 230 Kth Smallest Element in a BST

    Algorithm:
    DFS (k, root)
        if root is a leaf:
            return 1, root.val;

        k1, val1 = DFS(k, root.left)
        if k1 == k : return k1, val1

        if (k1 + 1 == k) {
            return root.val;
            return k;
        }

        k2, val2 = DFS(k - k1 - 1, root.right)

        return k1 + k2 + 1, val2

    Idea:
    the smallest element is the left most child of the left most subtree.
    The largest element is the right most child of right most subtree.
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
     * @brief Gets the kth smallest element in the BST.
     * @param root TreeNode* root of the BST.
     * @param k Int k, denoting the kth smallest element needed
     * @returns Int kth smallest element value.
     */
    int kthSmallest(TreeNode* root, int k) {
        int kth_smallest_val;
        inorder_traversal(root, k, kth_smallest_val);
        return kth_smallest_val;
    }

private:
    /**
     * @brief Traverses the BST subtree inorder from the root and get the kth smallest element.
     * If the num_left < k, then returns the num_left th element.
     * @param root TreeNode* root of the subtree.
     * @param k Int kth smallest element needed
     * @param [out] kth_smallest_val Int kth smallest value.
     * @returns Int k or the number of elements in the subtree if smaller than k.
     */
    int inorder_traversal(TreeNode* root, int k, int &kth_smallest_val) {
        if(!root) {
            return 0;
        }

        if (!root->left && !root->right) {
            kth_smallest_val = root->val;
            return 1;
        }

        int num_elements_left = inorder_traversal(root->left, k, kth_smallest_val);
        if (num_elements_left == k) {
            return k;
        }

        if (num_elements_left + 1 == k) {
            kth_smallest_val = root->val;
            return k;
        }

        int num_elements_right = inorder_traversal(root->right, k-num_elements_left-1, kth_smallest_val);
        return num_elements_left + num_elements_right + 1;
    }
};