class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int n = words.size();
        int i = 0;

        while (i < n) {
            int j = i;
            int lineLength = 0;

            // Find how many words fit in the current line
            while (j < n && lineLength + words[j].size() + (j - i) <= maxWidth) {
                lineLength += words[j].size();
                j++;
            }

            int numWords = j - i;
            int spaces = maxWidth - lineLength;

            string line;

            // Last line or only one word -> Left Justify
            if (j == n || numWords == 1) {
                line += words[i];
                for (int k = i + 1; k < j; k++) {
                    line += " ";
                    line += words[k];
                }
                line += string(maxWidth - line.size(), ' ');
            }
            else {
                int gaps = numWords - 1;
                int evenSpace = spaces / gaps;
                int extraSpace = spaces % gaps;

                for (int k = i; k < j - 1; k++) {
                    line += words[k];
                    line += string(evenSpace + (extraSpace > 0 ? 1 : 0), ' ');
                    if (extraSpace > 0) extraSpace--;
                }
                line += words[j - 1];
            }

            ans.push_back(line);
            i = j;
        }

        return ans;
    }
};