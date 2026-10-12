class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int h = health - grid[0][0];
        if (!h) return false;
        queue<pair<int, pair<int, int>>> q;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n));
        q.push({h, {0, 0}});
        visited[0][0] = h;
        while (q.size()) {
            auto item = q.front();
            int h = item.first;
            auto position = item.second;
            int i = position.first, j = position.second;
            if (i == m - 1 && j == n - 1) {
                return true;
            }
            if (j && visited[i][j-1] < h - grid[i][j-1] && h - grid[i][j-1] != 0) { // left
                q.push({h - grid[i][j-1], {i, j - 1}});
                visited[i][j-1] = h - grid[i][j-1];
            }
            if (j + 1 < n && visited[i][j+1] < h - grid[i][j+1] && h - grid[i][j+1] != 0) { // right
                q.push({h - grid[i][j+1], {i, j + 1}});
                visited[i][j+1] = h - grid[i][j+1];
            }
            if (i && visited[i-1][j] < h - grid[i-1][j] && h - grid[i-1][j] != 0) { // top
                q.push({h - grid[i-1][j], {i - 1, j}});
                visited[i-1][j] = h - grid[i-1][j];
            }
            if (i + 1 < m && visited[i+1][j] < h - grid[i+1][j] && h - grid[i+1][j] != 0) { // down
                q.push({h - grid[i+1][j], {i + 1, j}});
                visited[i+1][j] = h - grid[i+1][j];
            }
            q.pop();
        }
        return false;
    }
};