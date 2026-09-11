class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        for (char ch : s) {
            if (ch == '(' || ch == '{' || ch == '[') {
                stack.push_back(ch == '(' ? ch + 1 : ch + 2);
            } else {
                if (stack.empty() || stack[stack.size() - 1] != ch) {
                    return false;
                }
                stack.pop_back();
            }
        }
        return stack.empty();
    }
};