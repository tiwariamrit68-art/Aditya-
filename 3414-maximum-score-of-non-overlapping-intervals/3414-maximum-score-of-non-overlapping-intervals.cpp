class Solution {
public:
    struct Node {
        long long score;
        vector<int> ids;
    };

    bool better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: left, right, weight, original index
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[0] < y[0];
        });

        // p[i] = number of intervals before i that are compatible
        // We need previous right < current left.
        vector<int> rights(n);

        for (int i = 0; i < n; i++)
            rights[i] = a[i][1];

        vector<int> p(n);

        for (int i = 0; i < n; i++) {
            p[i] = lower_bound(
                rights.begin(),
                rights.begin() + i,
                a[i][0]
            ) - rights.begin();
        }

        // dp[k][i] = best answer using at most k intervals
        // among first i intervals.
        vector<vector<Node>> dp(
            5, vector<Node>(n + 1, {0, {}})
        );

        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= n; i++) {

                // Don't take current interval
                Node skip = dp[k][i - 1];

                // Take current interval
                Node take = dp[k - 1][p[i - 1]];

                take.score += a[i - 1][2];
                take.ids.push_back((int)a[i - 1][3]);

                // Indices must be sorted for lexicographical comparison
                sort(take.ids.begin(), take.ids.end());

                if (better(take, skip))
                    dp[k][i] = take;
                else
                    dp[k][i] = skip;
            }
        }

        return dp[4][n].ids;
    }
};