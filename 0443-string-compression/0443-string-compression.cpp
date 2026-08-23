class Solution {
public:
    void splitNums(vector<char>& chars, int &i, int count) {
        int start = i;
        while (count != 0) {
            chars[i++] = (count % 10) + '0';
            count /= 10;
        }
        reverse(chars.begin() + start, chars.begin() + i);
    }
    int compress(vector<char>& chars) {
        int count = 0, i = 0;
        char lastCh = chars[0];
        for (char ch : chars) {
            if (lastCh == ch) {
                count++;
            } else {
                if (count > 1) {
                    chars[i++] = lastCh;
                    splitNums(chars, i, count);
                } else {
                    chars[i++] = lastCh;
                }
                lastCh = ch;
                count = 1;
            }
        }
        if (count > 1) {
            chars[i++] = lastCh;
            splitNums(chars, i, count);
        } else {
            chars[i++] = lastCh;
        }
        return i;
    }
};