class Solution {
public:
    int countLargestGroup(int n) {
        int freq[37] = {}, maxi = 0;
        for (int i = 1; i <= n; ++i) {
            int x = i, sum = 0;
            while (x != 0) {
                sum += x % 10;
                x /= 10;
            }
            maxi = max(maxi, ++freq[sum]);
        }
        int count = 0;
        for (int occ : freq) {
            count += maxi == occ;
        }
        return count;
    }
};