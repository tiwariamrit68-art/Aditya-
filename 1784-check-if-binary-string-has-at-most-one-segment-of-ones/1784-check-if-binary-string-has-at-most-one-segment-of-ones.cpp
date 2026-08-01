class Solution {
public:
    bool checkOnesSegment(string s) {
        bool ended = false;

        for (int i = 1; i < s.size(); i++) {
            if (s[i - 1] == '1' && s[i] == '0') {
                ended = true;
            }
            if (ended && s[i] == '1') {
                return false;
            }
        }

        return true;
    }
};