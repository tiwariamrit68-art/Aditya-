class Solution {
public:
    char processStr(string s, long long k) {
        int n = s.size();

        // len[i] = length of result after processing s[0..i]
        vector<long long> len(n);

        long long cur = 0;

        for (int i = 0; i < n; i++) {
            char c = s[i];

            if (c >= 'a' && c <= 'z') {
                cur++;
            }
            else if (c == '*') {
                if (cur > 0)
                    cur--;
            }
            else if (c == '#') {
                cur = min(1000000000000000LL, cur * 2);
            }
            // '%' does not change length

            len[i] = cur;
        }

        // k is 0-indexed
        if (k >= cur)
            return '.';

        // Work backwards
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];

            if (c >= 'a' && c <= 'z') {
                // This character was appended at the end.
                if (k == len[i] - 1)
                    return c;

                // Otherwise k remains unchanged.
            }
            else if (c == '*') {
                // '*' removed the last character.
                // Existing positions are unchanged.
            }
            else if (c == '#') {
                // Before #:
                // result = old + old
                //
                // If k is in the second half,
                // map it back to the first half.
                long long oldLen = len[i] / 2;

                if (oldLen > 0 && k >= oldLen)
                    k -= oldLen;
            }
            else if (c == '%') {
                // Reverse operation.
                k = len[i] - 1 - k;
            }
        }

        return '.';
    }
};