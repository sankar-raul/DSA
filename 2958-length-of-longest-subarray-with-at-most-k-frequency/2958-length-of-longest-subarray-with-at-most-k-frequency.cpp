class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int i = 0, max_seq = 0;
        unordered_map<int, int> freq;
        for (int j = 0; j < nums.size(); ++j) {
            if (freq[nums[j]] >= k) {
                while (nums[i++] != nums[j]) {
                    freq[nums[i-1]]--;
                    continue;
                }
            }  else {
                freq[nums[j]]++;
                max_seq = max(max_seq, j - i);
            }
        }
        return max_seq + 1;
    }
};