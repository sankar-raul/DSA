class Solution {
public:
    int n, m;
    int dfs(int i, int j, vector<vector<int>>& vis, vector<vector<int>>& grid, int& id) {
        if (vis[i][j] == id) {
            return 0;
        }
        vis[i][j] = id;
        int res = grid[i][j];
        // left
        if (j && vis[i][j-1] != id && grid[i][j-1] != 0) {
            res = max(res, dfs(i, j - 1, vis, grid, id) + grid[i][j]);
        }
        // right
        if (j + 1 < n && vis[i][j+1] != id && grid[i][j+1] != 0) {
            res = max(res, dfs(i, j + 1, vis, grid, id) + grid[i][j]);
        }
        // top
        if (i && vis[i-1][j] != id && grid[i-1][j] != 0) {
            res = max(res, dfs(i-1, j, vis, grid, id) + grid[i][j]);
        }
        // down
        if (i + 1 < m && vis[i+1][j] != id && grid[i+1][j] != 0) {
            res = max(res, dfs(i+1, j, vis, grid, id) + grid[i][j]);
        }
        vis[i][j]--;
        return res;
    }
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int maxi = 0;
        vector<vector<int>> vis(m, vector<int>(n));
        int id = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                maxi = max(maxi, dfs(i, j, vis, grid, id));
                ++id;
            }
        }
        return maxi;
    }
};