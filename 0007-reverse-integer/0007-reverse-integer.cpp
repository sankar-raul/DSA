class Solution {
public:
    int reverse(int x) {
        long long rev = 0;
        while (x != 0) {
            int digit = x % 10;
            rev = rev * 10 + digit;
            x /= 10;
        }
        cout << rev << endl;
        return abs(rev) > INT_MAX ? 0 : rev;
    }
};