class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        // dp = number of distinct subsequences including empty subsequence
        long long dp = 1;

        // last[c] = dp value before the previous occurrence of character c
        vector<long long> last(26, 0);

        for (char c : s) {
            int idx = c - 'a';

            long long newDp = (2 * dp) % MOD;

            // Remove duplicates caused by previous occurrence
            newDp = (newDp - last[idx] + MOD) % MOD;

            // Save current dp before updating
            last[idx] = dp;

            dp = newDp;
        }

        // Remove empty subsequence
        return (dp - 1 + MOD) % MOD;
    }
};