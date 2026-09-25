class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        queue<int> q;
        string res = "";
        int hike = numRows + (numRows - 2), n = s.size(), i;
        for (i = 0; i < n; i += hike) {
            res += s[i];
            if (i - 1 > 0) {
                q.push(i-1);
            }
            if (i + 1 < n) {
                q.push(i+1);
            }
        }
        if (i - hike <= n)
            q.push(i - 1);
        int count = 0;
        while (count < numRows - 1) {
            int j = 0;
            int len = q.size();
            while (len--) {
                int idx = q.front();
                q.pop();
                if ((numRows - count > 2 || j % 2 == 0) && idx < n)
                    res += s[idx];
                if (j % 2 == 0 && idx + 1 < n) {
                    q.push(idx + 1);
                } else if (j & 1 && numRows - count > 2) {
                    q.push(idx - 1);
                }
                j++;
            }
            count++;
        }
        return res;
    }
};