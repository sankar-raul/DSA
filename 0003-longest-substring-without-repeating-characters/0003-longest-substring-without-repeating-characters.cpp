class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> lastSeen;
        int max_size = 0;
        int left = 0;
        for (int i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if (lastSeen.count(ch)) {
                left = max(left, lastSeen[ch] + 1);
            }
            lastSeen[ch] = i;
            max_size = max(max_size, i - left + 1);
        }
        return max_size;
    }
};