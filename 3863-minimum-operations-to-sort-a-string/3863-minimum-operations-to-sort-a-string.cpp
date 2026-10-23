class Solution {
public:
    int minOperations(string s) {
        int mn = 0, mx = 0;
        bool is_sorted = true;
        for (int i = 1; i < s.size(); ++i) {
            is_sorted &= s[i-1] <= s[i];
            if (s[mn] > s[i]) {
                mn = i;
            } else if (s[mx] <= s[i]) {
                mx = i;
            }
        }
        if (is_sorted) return 0;
        if (s.size() == 2) return -1;
        if (mn == 0 || mx == s.size() - 1) return 1;
        if (mx == 0 && mn == s.size() - 1) return 3;
        return 2;
    }
};