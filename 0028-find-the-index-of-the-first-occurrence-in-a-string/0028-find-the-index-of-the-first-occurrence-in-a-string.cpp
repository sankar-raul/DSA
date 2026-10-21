class Solution {
public:
    vector<int> cal_lps(string &str) {
        int i = 1, len = 0, n = str.size();
        vector<int> lps(n);
        lps[0] = 0;
        while (i < n) {
            if (str[i] == str[len]) {
                len++;
                lps[i] = len;
                i++;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
        return lps;
    }
    int strStr(string haystack, string needle) {
        vector<int> lps = cal_lps(needle);
        int i = 0, j = 0, n = haystack.size(), m = needle.size(), idx = -1;
        while (i < n && j < m) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
                if (j == m) return i - m;
            } else if (j) {
                j = lps[j-1];
            } else {
                i++;
            }
        }
        return -1;
    }
};