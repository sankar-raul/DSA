class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(),  [](int a, int b) {
            return abs(a) < abs(b);
        });
        long long res = 0;
        int half = nums.size() / 2;
        int j = nums.size() - 1;
        for (int i = 0; i < half; ++i) {
            long long a = nums[i] * nums[i];
            long long b = nums[j] * nums[j];
            res += b - a;
            --j;
        }
        if (nums.size() & 1) {
            res += nums[j] * nums[j];
        }
        return res;
    }
};