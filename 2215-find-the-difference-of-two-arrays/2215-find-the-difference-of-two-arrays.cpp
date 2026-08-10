class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> h1;
        unordered_map<int, int> h2;
        vector<vector<int>> ans = {{}, {}};
        for (int num : nums1) {
            h1[num]++;
        }
        for (int num : nums2) {
            if (!h1[num]) {
                ans[1].push_back(num);
                h1[num]--;
            } else {
                h2[num]++;
            }
        }
        for (int num : nums1) {
            if (!h2[num]) {
                ans[0].push_back(num);
                h2[num]--;
            }
        }
        return ans;
    }
};