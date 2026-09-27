class Solution {
public:
    string reverseParentheses(string s) {
        vector<int> stk;
        string ans = "";
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push_back(i+1);
            } else if (s[i] == ')') {
                int idx = stk[stk.size() - 1];
                stk.pop_back();
                reverse(s.begin() + idx, s.begin() + i);
                if (stk.empty()) {
                    for (int j = idx; j < i; ++j) {
                        if (s[j] != '(' && s[j] != ')') {
                            ans += s[j];
                        }
                    }
                }
            } else if (stk.empty()) {
                ans += s[i];
            }
        }
        return ans;
    }
};