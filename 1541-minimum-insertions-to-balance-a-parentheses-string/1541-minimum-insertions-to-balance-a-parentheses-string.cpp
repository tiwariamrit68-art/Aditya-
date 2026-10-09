
class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } else {
                // Check whether this ')' has another ')' after it
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } else {
                    // Insert a missing ')'
                    insertions++;
                }

                if (open > 0) {
                    open--;
                } else {
                    // Insert a missing '('
                    insertions++;
                }
            }
        }

        // Every remaining '(' needs two ')'
        insertions += open * 2;

        return insertions;
    }
};