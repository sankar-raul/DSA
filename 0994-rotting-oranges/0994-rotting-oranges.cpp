class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int m = grid.size(), n = grid[0].size(), fresh = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.emplace(i, j);
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        if (!fresh) return 0;
        if (q.empty()) {
            return -1;
        }
        int minutes = 0;
        while (q.size()) {
            int len = q.size();
            bool isWorked = false;
            while (len--) {
                auto pair = q.front();
                int i = pair.first, j = pair.second;
                int left = j - 1 >= 0 ? grid[i][j-1] : 0;
                int right = j + 1 < n ? grid[i][j+1] : 0;
                int top = i - 1 >= 0 ? grid[i-1][j] : 0;
                int bottom = i + 1 < m ? grid[i+1][j] : 0;
                if (left == 1) {
                    fresh--;
                    q.emplace(i, j - 1);
                    grid[i][j-1] = -grid[i][j-1];
                    isWorked = true;
                }
                if (right == 1) {
                    fresh--;
                    q.emplace(i, j + 1);
                    grid[i][j+1] = -grid[i][j+1];
                    isWorked = true;
                }
                if (top == 1) {
                    fresh--;
                    q.emplace(i - 1, j);
                    grid[i-1][j] = -grid[i-1][j];
                    isWorked = true;
                }
                if (bottom == 1) {
                    fresh--;
                    q.emplace(i + 1, j);
                    grid[i+1][j] = -grid[i+1][j];
                    isWorked = true;
                }
                q.pop();
            }
            minutes += isWorked;
        }
        return fresh ? -1 : minutes;
    }
};