class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int i = 0, j = n - 1;
        vector<int> res;
        int from = -1, to = -2;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (nums[mid] == target) {
                from = to = mid;
                int n_mid = mid + 1;
                --mid;
                while (mid >= 0 && nums[mid] == target) {
                    from = mid--;
                }
                while (n_mid < n && nums[n_mid] == target) {
                    to = n_mid++;
                }
                break;
            } else if (target < nums[mid]) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }

        for (int i = from; i <= to; i++) {
            res.push_back(i);
        }
        return res;
    }
};