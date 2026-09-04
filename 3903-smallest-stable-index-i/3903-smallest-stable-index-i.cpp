class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffix_min(n);
        suffix_min[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; --i) {
            suffix_min[i] = min(suffix_min[i+1], nums[i]);
        }
        int maxi = 0, gap;
        for (int i = 0; i < n; ++i) {
            maxi = max(maxi, nums[i]);
            gap = maxi - suffix_min[i];
            if (gap <= k) return i;
        }
        return -1;
    }
};