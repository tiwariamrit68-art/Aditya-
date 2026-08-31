/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check local maximum or local minimum
            bool critical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (critical) {
                if (first == -1) {
                    // First critical point
                    first = pos;
                } else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - last);
                }

                last = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        // Need at least two critical points
        if (first != -1 && first != last) {
            ans[0] = minDist;
            ans[1] = last - first;
        }

        return ans;
    }
};