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
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    queue<TreeNode*> q;  // Queue for BFS traversal.
    vector<vector<int>> result; // To be returned
    if(!root) return result;
    q.push(root);   // putting root inside the queue.
    int flag = 0;   // flag which decides which way to traverse.1 is right-left, 0 is left-right    
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
        if(first_element_queue->right)q.push(first_element_queue->right); 
        }
    // One level traversed completely.   
    if (level.size()>0)
    {   
       if (flag!=0){
            reverse(level.begin(), level.end());
            result.push_back(level);
            flag = 0;
        }
        else{
        result.push_back(level);
        flag = 1;
        }
        
    }
   
    }
    return result; 
        
    }
};
