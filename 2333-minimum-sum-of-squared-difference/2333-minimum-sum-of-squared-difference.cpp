
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<int> diff(nums1.size());
        int mx = 0;

        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
        }

        if (k == 0) {
            long long ans = 0;
            for (int d : diff)
                ans += 1LL * d * d;
            return ans;
        }

        long long left = 0, right = mx;

        while (left < right) {
            long long mid = (left + right) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid)
                    needed += d - mid;
            }

            if (needed <= k)
                right = mid;
            else
                left = mid + 1;
        }

        long long level = left;
        long long used = 0;
        long long ans = 0;

        for (int d : diff) {
            if (d > level) {
                used += d - level;
                ans += level * level;
            } else {
                ans += 1LL * d * d;
            }
        }

        long long remaining = k - used;

        // Reduce remaining differences from level to level - 1.
        for (int d : diff) {
            if (remaining == 0) break;
            if (d >= level && level > 0) {
                ans -= level * level - (level - 1) * (level - 1);
                remaining--;
            }
        }

        return ans;
    }
};
