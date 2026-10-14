class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        int s = sum;
        string res;
        while (num--) {
            res += sum < 0 ? '0' : sum <= 9 ? '0' + sum : '9'; 
            sum -= 9;
        }
        return sum > 0 ? "" : res;
    }
};