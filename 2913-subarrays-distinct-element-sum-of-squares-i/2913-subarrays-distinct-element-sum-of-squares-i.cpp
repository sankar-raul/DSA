class Solution {
public:
    int sumCounts(vector<int>& nums) {
        unordered_map<int, bool> look;
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int unique = 0;
            for (int j = i; j < nums.size(); ++j) {
                if (!look[nums[j]]) {
                    unique++;
                }
                look[nums[j]] = true;
                res += unique * unique;
            }
            look.clear();
            unique = 0;
        }
        return res;
    }
};