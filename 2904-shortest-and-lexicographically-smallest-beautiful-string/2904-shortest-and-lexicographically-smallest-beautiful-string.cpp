class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int i = -1;
        int count = 0;
        int loc[] = {0, 0}; // i, j
        for (int j = 0; j < s.size(); ++j) {
            if (count >= k) {
                if (s[j] == '1') {
                    while (s[++i] != '1') {
                        // ಥ_ಥ
                    }
                    cout << loc[0] << " () " << loc[1] << endl; 
                    string_view slice_1(s.data() + loc[0], loc[1] - loc[0]);
                    string_view slice_2(s.data() + i, j - i + 1);
                    cout << slice_1 << " " << slice_2 << "  " << (slice_2 <= slice_1) << " >> " << j-i+1 << "==" << loc[1] - loc[0] << endl;
                    if ((loc[0] == loc[1]) || j-i+1 < loc[1] - loc[0] || (j - i+1 == loc[1] - loc[0] && slice_2 < slice_1)) {
                        loc[0] = i;
                        loc[1] = j + 1;
                    }
                } else {
                    if (loc[0] == loc[1]) {
                        loc[0] = i;
                        loc[1] = j;
                    }
                }
            } else {
                if (i == -1 && s[j] == '1') {
                    i = j;
                }
                count += s[j] == '1';
                cout << count << endl;
                if (count == k) {
                    string_view slice_1(s.data() + loc[0], loc[1] - loc[0]);
                    string_view slice_2(s.data() + i, j - i + 1);
                    cout << slice_1 << " " << slice_2 << "  " << (slice_2 <= slice_1) << " >> " << j-i+1 << "==" << loc[1] - loc[0] << endl;
                    if ((loc[0] == loc[1]) || j-i+1 < loc[1] - loc[0] || (j - i+1 == loc[1] - loc[0] && slice_2 < slice_1)) {
                        loc[0] = i;
                        loc[1] = j + 1;
                    }
                }
            }
        }
        // cout << loc[0] << loc[1];
        return s.substr(loc[0], loc[1] - loc[0]);
    }
};