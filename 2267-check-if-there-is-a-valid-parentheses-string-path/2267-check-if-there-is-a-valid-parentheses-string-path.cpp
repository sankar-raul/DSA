class Solution {
    int t[101][101][201];
    bool is_valid(int i, int j, vector<vector<char>>& grid, int open_count) {
        int n = grid.size(), m = grid[0].size();
        open_count += grid[i][j] == '(' ? 1 : -1;
        if (i == n - 1 && j == m - 1) return t[i][j][open_count] = open_count == 0;
        if (open_count < 0) return false;
        if (t[i][j][open_count] != -1) return t[i][j][open_count];
        bool right = j + 1 < m ? is_valid(i, j + 1, grid, open_count) : false;
        if (right) return t[i][j][open_count] = true;
        bool down = i + 1 < n ? is_valid(i + 1, j, grid, open_count) : false;
        return t[i][j][open_count] = down;
    }
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        if (grid[0][0] == ')' || grid[n - 1][m - 1] == '(' || m + n - 1 & 1) return false;
        memset(t, -1, sizeof(t));
        return is_valid(0, 0, grid, 0);
    }
};