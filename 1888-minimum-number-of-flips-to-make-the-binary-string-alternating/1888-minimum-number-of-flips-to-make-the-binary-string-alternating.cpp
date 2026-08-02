class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        string t = s + s;

        int diff1 = 0, diff2 = 0;
        int ans = INT_MAX;

        for (int i = 0; i < 2 * n; i++) {
            char c1 = (i % 2 == 0) ? '0' : '1';
            char c2 = (i % 2 == 0) ? '1' : '0';

            if (t[i] != c1) diff1++;
            if (t[i] != c2) diff2++;

            if (i >= n) {
                char p1 = ((i - n) % 2 == 0) ? '0' : '1';
                char p2 = ((i - n) % 2 == 0) ? '1' : '0';

                if (t[i - n] != p1) diff1--;
                if (t[i - n] != p2) diff2--;
            }

            if (i >= n - 1) {
                ans = min(ans, min(diff1, diff2));
            }
        }

        return ans;
    }
};