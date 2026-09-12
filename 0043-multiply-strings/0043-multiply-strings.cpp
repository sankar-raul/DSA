class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string result = "";
        for (int digit : res) {
            cout << digit << " ";
            if (!(result.empty() && !digit)) {
                result.push_back('0' + digit);
            }
        }
        return result.empty() ? "0" : result;
    }
};