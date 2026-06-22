class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long maxi = 0, s = 0;
        unordered_map<int, int> map;
        bool isDistinct = true;
        for (int i = 0; i < k; ++i) {
            if (map[nums[i]]) {
                isDistinct = false;
            }
            map[nums[i]]++;
            maxi += nums[i];
        }
        s = maxi;
        maxi = isDistinct ? maxi : 0;
        for (int i = k; i < nums.size(); ++i) {
            if (--map[nums[i-k]] == 0) map.erase(nums[i-k]);
            s -= nums[i-k];
            s += nums[i];
            map[nums[i]]++;
            if (map.size() == k) {
                maxi = max(maxi, s);
            }
        }
        return maxi;
    }
};