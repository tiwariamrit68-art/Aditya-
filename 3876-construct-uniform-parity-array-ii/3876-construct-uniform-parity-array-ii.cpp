class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;

        // Find the smallest odd number
        for (int x : nums1) {
            if (x % 2 == 1) {
                minOdd = min(minOdd, x);
            }
        }

        // Check if we can make all numbers odd
        bool allOdd = true;

        for (int x : nums1) {
            if (x % 2 == 0) {
                // Even - Odd = Odd
                // Need a smaller odd number
                if (minOdd >= x) {
                    allOdd = false;
                    break;
                }
            }
        }

        // Check if we can make all numbers even
        bool allEven = true;

        for (int x : nums1) {
            if (x % 2 == 1) {
                // An odd number needs another smaller odd number
                if (minOdd == x) {
                    allEven = false;
                    break;
                }
            }
        }

        return allOdd || allEven;
    }
};