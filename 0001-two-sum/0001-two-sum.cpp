class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        int c;
        for (int i = 0; i < nums.size(); i++) {
            c = target - nums[i];
            if (map.find(nums[i]) != map.end())
                return {map[nums[i]], i};
            map[c] = i;
        }
        return {};
    }
};