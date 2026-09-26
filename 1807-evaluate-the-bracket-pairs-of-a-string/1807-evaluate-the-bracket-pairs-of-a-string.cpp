class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key -> value
        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                int j = i + 1;
                string key;

                // Extract key
                while (s[j] != ')') {
                    key += s[j];
                    j++;
                }

                // Replace with value or '?'
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += '?';

                // Skip the entire bracket pair
                i = j;
            }
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};