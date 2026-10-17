class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size(), n = image[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        int starting_color = image[sr][sc];
        image[sr][sc] = color;
        while (q.size()) {
            auto& p = q.front();
            int i = p.first, j = p.second;
            if (j && !visited[i][j-1] && image[i][j-1] == starting_color) { // left
                q.push({i, j-1});
                image[i][j-1] = color;
                visited[i][j-1] = true;
            }
            if (j + 1 < n && !visited[i][j+1] && image[i][j+1] == starting_color) { // right
                q.push({i, j+1});
                image[i][j+1] = color;
                visited[i][j + 1] = true;
            }
            if (i && !visited[i-1][j] && image[i-1][j] == starting_color) { // top
                q.push({i-1, j});
                image[i-1][j] = color;
                visited[i-1][j] = true;
            }
            if (i + 1 < m && !visited[i + 1][j] && image[i+1][j] == starting_color) { // down
                q.push({i + 1, j});
                image[i+1][j] = color;
                visited[i+1][j] = true;
            }
            q.pop();
        }
        return image;
    }
};