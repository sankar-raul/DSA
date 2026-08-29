class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> duplicates;
        for (int num : nums) {
            int idx = abs(num) - 1;
            if (nums[idx] < 0) {
                duplicates.push_back(abs(num));
            } else {
                nums[idx] = -nums[idx];
            }
        }
        return duplicates;
    }
};