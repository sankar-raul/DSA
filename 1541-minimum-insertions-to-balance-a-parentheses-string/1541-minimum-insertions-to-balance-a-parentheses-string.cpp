class Solution {
public:
    int minInsertions(string s) {
        int neg_count = 0, res = 0;
        double count = 0;
        for (char ch : s) {
            if (ch == '(') {
                if (fmod(count, 1.0) == 0.5) {
                    res += 1;
                    count += -0.5 + 1;
                } else {
                    count++;
                }
                if (neg_count) {
                    res += neg_count / 2;
                    res += (neg_count % 2) * 2;
                    neg_count = 0;
                }
            } else {
                count -= 0.5;
                if (count < 0) {
                    neg_count++;
                    count = 0;
                }
            }
        }
        if (neg_count) {
            res += neg_count / 2;
            res += (neg_count % 2) * 2;
            neg_count = 0;
        }
        res += count * 2;
        return res;
    }
};