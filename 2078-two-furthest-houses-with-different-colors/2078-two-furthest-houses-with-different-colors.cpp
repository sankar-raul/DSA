class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int j[] = {0,0}, k[] = {n-1, n-1};
        int m = -1;
        for (int i = 0; i <= n / 2; i++) {
            if (colors[j[0]] == colors[k[0]]) {
                --k[0];
            } else {
                m = max(abs(j[0] - k[0]), m);
            }
            if (colors[j[1]] == colors[k[1]]) {
                ++j[1];
            } else {
                m = max(abs(j[1] - k[1]), m);
            }
        }
        return m;
    }
};