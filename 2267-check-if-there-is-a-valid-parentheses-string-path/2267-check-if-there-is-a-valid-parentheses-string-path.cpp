class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Path length must be even for a valid parentheses string
        if ((m + n - 1) % 2 != 0)
            return false;

        // dp[j][balance] = whether we can reach (i,j)
        // with this parentheses balance
        vector<vector<bool>> dp(n, vector<bool>(m + n, false));

        if (grid[0][0] == ')')
            return false;

        dp[0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                int change = (grid[i][j] == '(') ? 1 : -1;

                vector<bool> cur(m + n, false);

                for (int balance = 0; balance <= m + n; balance++) {
                    bool possible = false;

                    // From top
                    if (i > 0 && balance - change >= 0)
                        possible |= dp[j][balance - change];

                    // From left
                    if (j > 0 && balance - change >= 0)
                        possible |= dp[j - 1][balance - change];

                    if (possible && balance >= 0)
                        cur[balance] = true;
                }

                dp[j] = cur;
            }
        }

        return dp[n - 1][0];
    }
};