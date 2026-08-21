class Solution {
public:
    long long gcdll(long long a, long long b) {
        return b == 0 ? a : gcdll(b, a % b);
    }

    long long lcmll(long long a, long long b) {
        return a / gcdll(a, b) * b;
    }

    long long countValid(long long x, vector<int>& coins) {
        int n = coins.size();
        long long count = 0;

        // Inclusion-Exclusion
        for (int mask = 1; mask < (1 << n); mask++) {
            long long lcm = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    lcm = lcmll(lcm, coins[i]);

                    if (lcm > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid) continue;

            long long multiples = x / lcm;

            if (bits % 2 == 1)
                count += multiples;
            else
                count -= multiples;
        }

        return count;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countValid(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};