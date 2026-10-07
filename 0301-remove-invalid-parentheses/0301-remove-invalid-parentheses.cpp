class Solution {
public:
    int n = 0;
    void valid(int idx, int d, string c_s, string& s, set<string>& ans) {
        if (s.size() == idx) {
            if (d == 0 && c_s.size() == n) {
                ans.insert(c_s);
            }
            return;
        }
        if (s[idx] == '(' || s[idx] == ')') {
            if (d + (s[idx] == '(' ? 1 : -1) >= 0 && c_s.size() < n) valid(idx+1, d + (s[idx] == '(' ? 1 : -1), c_s + s[idx], s, ans);
            valid(idx+1, d, c_s, s, ans);
        } else {
            c_s += s[idx];
            valid(idx + 1, d, c_s, s, ans);
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        set<string> ans;
        int d = 0, rem = 0;
        for (char ch : s) {
            if (ch == '(') {
                d++;
            } else if (ch == ')') {
                d--;
                if (d < 0) {
                    d = 0;
                    rem++;
                }
            }
        }
        n = s.size() - (d + rem);
        cout << n;
        valid(0, 0, "", s, ans);
        int maxi = 0;
        for (string st : ans) {
            maxi = max(maxi, (int)st.size());
        }
        return ans.empty() ? vector<string>{""} : vector<string>(ans.begin(), ans.end());
    }
};