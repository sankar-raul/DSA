class Solution {
public:
    int countDigitOccurrences(vector<int>& nums, int digit) {
        int count = 0;
        for (int num : nums) {
            while (num != 0) {
                int rem = num % 10;
                count += digit == rem;
                num /= 10;
            }
        }
        return count;
    }
};