class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int current_sum = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1] + 1) {
                current_sum += nums[i];
            } else {
                break;
            }
        }
        sort(nums.begin(), nums.end());
        for (int num : nums) {
            if (current_sum == num) {
                current_sum++;
            }
        }
        return current_sum;
    }
};