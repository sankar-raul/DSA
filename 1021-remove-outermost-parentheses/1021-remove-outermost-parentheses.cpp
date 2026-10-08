class Solution {
public:
    string removeOuterParentheses(string s) {
        int depth = 0;
        string res = "";
        for (char ch : s) {
            if (ch == '(') {
                if (depth) res += ch;
                depth++;
            } else {
                depth--;
                if (depth) res += ch;
            }
        }
        return res;
    }
};