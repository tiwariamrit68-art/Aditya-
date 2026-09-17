class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left++];
            }

            // Carry forward the best subarray found so far
            if (right > 0)
                best[right] = best[right - 1];

            // Found a subarray with sum == target
            if (sum == target) {
                int len = right - left + 1;

                // Previous subarray must end before 'left'
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, len + best[left - 1]);
                }

                // This is the best single subarray ending at 'right'
                best[right] = min(best[right], len);
            }
        }

        return ans == INF ? -1 : ans;
    }
};