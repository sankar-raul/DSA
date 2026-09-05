class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        int suffix[n];
        suffix[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; --i) {
            suffix[i] = min(suffix[i+1], nums[i]);
        }
        int maxi = 0;
        for (int i = 0; i < n; i++) {
            maxi = max(maxi, nums[i]);
            if (maxi - suffix[i] <= k) return i;
        }
        return -1;
    }
};