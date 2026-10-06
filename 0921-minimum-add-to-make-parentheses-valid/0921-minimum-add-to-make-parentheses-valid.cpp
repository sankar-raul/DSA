class Solution {
public:
    int minAddToMakeValid(string s) {
        if (s.size() == 0) return 0;
        int count = 0, rem = 0;
        for (char ch : s) {
            if (ch == '(') {
                count++;
            } else {
                count--;
                if (count < 0) {
                    rem++;
                    count = 0;
                }
            }
        }
        return count + rem;
    }
};