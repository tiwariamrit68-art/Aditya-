class Solution {
public:
    static const int MOD = 1000000007;

    int numberOfSets(int n, int k) {
        vector<long long> dp(k + 1, 0);
        vector<long long> sum(k + 1, 0);

        dp[0] = 1;

        for (int i = 1; i < n; i++) {
            // sum[j] represents the number of ways
            // to start a new segment for j segments.
            for (int j = 1; j <= min(k, i); j++) {
                sum[j] = (sum[j] + dp[j - 1]) % MOD;
            }

            // Update dp from right to left
            for (int j = 1; j <= k; j++) {
                dp[j] = (dp[j] + sum[j]) % MOD;
            }
        }

        return dp[k];
    }
};