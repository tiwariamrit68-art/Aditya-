class Solution {
public:
    int minOperations(string s) {
        int count0 = 0, count1 = 0;

        for (int i = 0; i < s.size(); i++) {
            char expected0 = (i % 2 == 0) ? '0' : '1';
            char expected1 = (i % 2 == 0) ? '1' : '0';

            if (s[i] != expected0) count0++;
            if (s[i] != expected1) count1++;
        }

        return min(count0, count1);
    }
};