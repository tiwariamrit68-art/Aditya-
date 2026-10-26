class Solution {
public:
    int m, n;
    vector<vector<bool>> vis;
    long long sum;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    void dfs(int i, int j, vector<vector<int>>& grid) {
        vis[i][j] = true;
        sum += grid[i][j];

        for (int d = 0; d < 4; d++) {
            int x = i + dx[d];
            int y = j + dy[d];

            if (x >= 0 && x < m && y >= 0 && y < n &&
                !vis[x][y] && grid[x][y] > 0) {
                dfs(x, y, grid);
            }
        }
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();
        vis.assign(m, vector<bool>(n, false));

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0 && !vis[i][j]) {
                    sum = 0;
                    dfs(i, j, grid);

                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};