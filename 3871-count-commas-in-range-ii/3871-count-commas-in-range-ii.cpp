class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        // Numbers >= 1000 have at least 1 comma.
        // Numbers >= 1,000,000 have at least 2 commas, etc.
        long long p = 1000;

        while (p <= n) {
            ans += n - p + 1;

            // Prevent overflow (not really needed for n <= 1e15,
            // but makes the code safe).
            if (p > n / 1000)
                break;

            p *= 1000;
        }

        return ans;
    }
};