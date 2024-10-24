/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
/* Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root). */


class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
    queue<TreeNode*> q;  // Queue for BFS traversal.
    vector<vector<int>> result; // To be returned
    if(!root) return result;
    q.push(root);   // putting root inside the queue.   
    while (q.size()>0)
    {
    vector<int> level;   // To store elements of each level.
    int length_of_queue = q.size();
    TreeNode* first_element_queue = new TreeNode();
    for (int i = 0; i<length_of_queue;i++)
    {
        first_element_queue = q.front();
        q.pop();
        level.push_back(first_element_queue->val);
        if(first_element_queue->left)q.push(first_element_queue->left);
        if(first_element_queue->right)q.push(first_element_queue->right); }
       
    if (level.size()>0){result.push_back(level);}
    }
    reverse(result.begin(),result.end());
    return result;    
    }
};
