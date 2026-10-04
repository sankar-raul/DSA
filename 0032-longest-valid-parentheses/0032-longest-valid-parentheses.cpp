class Solution {
public:
    int longestValidParentheses(string s) {
        int i = 0, j = 0, n = s.size();
        int open = 0, closed = 0;
        int maxi = 0;
        while (j < n) {
            if (s[j] == '(') {
                open++;
            } else {
                closed++;
            }
            if (open == closed) {
                maxi = max(maxi, open + closed);
            } else if (closed > open) {
                closed = open = 0;
            }
            j++;
        }
        j = n - 1, open = closed = 0;
        while (j >= 0) {
            if (s[j] == '(') {
                open++;
            } else {
                closed++;
            }
            if (open == closed) {
                maxi = max(maxi, open + closed);
            } else if (open > closed) {
                closed = open = 0;
            }
            j--;
        }
        return maxi;
    }
};