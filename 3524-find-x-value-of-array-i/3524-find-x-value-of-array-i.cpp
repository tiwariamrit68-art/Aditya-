class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at previous position
        // whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);

            int val = num % k;

            // Start a new subarray with nums[i]
            ndp[val]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r]) {
                    int newRem = (long long)r * val % k;
                    ndp[newRem] += dp[r];
                }
            }

            // Every subarray ending here contributes to the answer
            for (int r = 0; r < k; r++) {
                ans[r] += ndp[r];
            }

            dp = ndp;
        }

        return ans;
    }
};