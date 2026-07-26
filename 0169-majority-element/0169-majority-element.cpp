class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m;
        int maj = nums[0];
        for (int n : nums) {
            if (++m[n] > m[maj]) {
                maj = n;
            }
        }
        return maj;
    }
};