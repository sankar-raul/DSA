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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> q;
        vector<long long> levelSums;
        q.push(root);
        while (!q.empty()) {
            vector<TreeNode*> level;
            long long sum = 0;
            while (!q.empty()) {
                sum += q.front()->val;
                level.push_back(q.front());
                q.pop();
            }
            levelSums.push_back(sum);
            for (TreeNode* node : level) {
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        if (k > levelSums.size()) return -1;
        sort(levelSums.begin(), levelSums.end(), greater<long long>());
        return levelSums[k-1];
    }
};