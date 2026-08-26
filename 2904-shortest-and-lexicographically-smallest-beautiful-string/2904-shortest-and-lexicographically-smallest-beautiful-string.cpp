class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        string ans = "";

        int left = 0;
        int ones = 0;

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            // We have exactly k ones
            if (ones == k) {
                
                // Remove leading zeros
                while (left <= right && s[left] == '0')
                    left++;

                string cur = s.substr(left, right - left + 1);

                // Check if this is better
                if (ans.empty() ||
                    cur.length() < ans.length() ||
                    (cur.length() == ans.length() && cur < ans)) {
                    ans = cur;
                }

                // Move left past the first 1
                if (s[left] == '1') {
                    ones--;
                    left++;
                }
            }
        }

        return ans;
    }
};