class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int unique = nums[0];
        for (int n : nums) {
            unique ^= n;
        }
        return unique ^ nums[0];
    }
};