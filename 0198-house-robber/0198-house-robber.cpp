class Solution {
public:
    int rob(vector<int>& nums) {
        int a, b, c;
        a = b = c = 0;
        for (int n : nums) {
            int tmp = c;
            c = n + max(a, b);
            a = b;
            b = tmp;
        }
        return max(b, c);
    }
};