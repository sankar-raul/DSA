class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int t_i = -1;
        // 1 2 3 5 6 6 7 8 5 4 t = 5 s = 6
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                t_i = t_i == -1 || abs(start-i) <= abs(start-t_i) ? i : t_i;
            }
        }
        return abs(start-t_i);
    }
};