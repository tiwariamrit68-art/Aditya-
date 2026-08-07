

class Solution {
public:
    vector<string> ans;

    bool valid(string part) {
        if (part.size() > 1 && part[0] == '0')
            return false;

        int num = stoi(part);
        return num >= 0 && num <= 255;
    }

    void backtrack(string &s, int idx, vector<string> &path) {
        // Found 4 parts
        if (path.size() == 4) {
            if (idx == s.size()) {
                string ip = path[0] + "." + path[1] + "." +
                            path[2] + "." + path[3];
                ans.push_back(ip);
            }
            return;
        }

        // Try taking 1, 2, or 3 digits
        for (int len = 1; len <= 3 && idx + len <= s.size(); len++) {
            string part = s.substr(idx, len);

            if (valid(part)) {
                path.push_back(part);
                backtrack(s, idx + len, path);
                path.pop_back();
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        vector<string> path;
        backtrack(s, 0, path);
        return ans;
    }
};