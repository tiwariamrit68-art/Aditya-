class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int sum1 = 0, sum2 = 0;
        int q1 = 0, q2 = 0;

        for (int i = 0; i < half; i++) {
            if (num[i] == '?')
                q1++;
            else
                sum1 += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                q2++;
            else
                sum2 += num[i] - '0';
        }

        int diff = sum1 - sum2;
        int qDiff = q1 - q2;

        // If the difference in '?' counts is odd,
        // Alice can always force a win.
        if (qDiff % 2 != 0)
            return true;

        // Bob can win only if the existing difference
        // can be exactly balanced by the '?' positions.
        return diff != -9 * qDiff / 2;
    }
};