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
    int nums = 0;
    vector<int> dfs(TreeNode* root) {
        if (!root) return {0, 0}; // sum, num of nodes
        auto left = dfs(root->left);
        auto right = dfs(root->right);
        int totalSum = left[0] + right[0] + root->val, count = left[1] + right[1] + 1;
        nums += totalSum / count == root->val;
        return { totalSum, count };
    }
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return nums;
    }
};