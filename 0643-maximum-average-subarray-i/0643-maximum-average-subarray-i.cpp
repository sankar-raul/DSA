class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sum = 0, m;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        m = sum;
        for (int i = k; i < nums.size(); ++i) {
            sum -= nums[i-k];
            sum += nums[i];
            m = max(m, sum);
        }
        return m / k;
    }
};