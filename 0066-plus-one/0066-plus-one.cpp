class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        // vector<int> res(digits.size());
        int remainder = 0;
        digits[digits.size()-1] += 1;
        for (int i = digits.size() - 1; i >= 0; --i) {
            digits[i] += remainder;
            remainder = 0;
            if (digits[i] > 9) {
                remainder = digits[i] - 9;
                digits[i] = 0;
            }
        }
        if (remainder) {
            digits.insert(digits.begin(), remainder);
        }
        return digits;
    }
};