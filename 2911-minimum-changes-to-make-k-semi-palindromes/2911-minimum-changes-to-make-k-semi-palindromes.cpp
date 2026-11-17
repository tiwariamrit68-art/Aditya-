class Solution {
public:
    int cost[205][205];

    // Minimum changes needed to make s[l..r] a semi-palindrome
    int getCost(string &s, int l, int r) {
        int len = r - l + 1;
        int ans = INT_MAX;

        // d must be a proper divisor of len
        for (int d = 1; d < len; d++) {
            if (len % d != 0) continue;

            int changes = 0;

            // There are d groups.
            // Each group contains positions:
            // i, i+d, i+2d, ...
            for (int start = 0; start < d; start++) {
                int left = start;
                int right = len - d + start;

                // Compare symmetric elements in this group
                while (left < right) {
                    if (s[l + left] != s[l + right])
                        changes++;

                    left += d;
                    right -= d;
                }
            }

            ans = min(ans, changes);
        }

        return ans;
    }

    int minimumChanges(string s, int k) {
        int n = s.size();

        // cost[l][r] = minimum changes to make s[l..r]
        // a semi-palindrome
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                cost[l][r] = getCost(s, l, r);
            }
        }

        // dp[i][j] = minimum changes to divide
        // first i characters into j parts
        const int INF = 1e9;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {
            for (int i = 2 * parts; i <= n; i++) {

                // Last substring starts at p
                // Need at least 2 characters per substring.
                for (int p = 2 * (parts - 1); p <= i - 2; p++) {
                    if (dp[p][parts - 1] == INF)
                        continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[p][parts - 1] + cost[p][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};