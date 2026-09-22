class Solution {
public:
    struct Node {
        int prod;
        long long pref[5];
        long long suff[5];
        long long sub[5];

        Node() {
            prod = 1;
            memset(pref, 0, sizeof(pref));
            memset(suff, 0, sizeof(suff));
            memset(sub, 0, sizeof(sub));
        }
    };

    int n, k;
    vector<Node> tree;

    Node merge(const Node& A, const Node& B) {
        Node C;

        C.prod = (A.prod * B.prod) % k;

        // Prefixes
        for (int i = 0; i < k; i++) {
            C.pref[i] += A.pref[i];

            int rem = (A.prod * i) % k;
            C.pref[rem] += B.pref[i];
        }

        // Suffixes
        for (int i = 0; i < k; i++) {
            C.suff[i] += B.suff[i];

            int rem = (i * B.prod) % k;
            C.suff[rem] += A.suff[i];
        }

        // Subarrays inside A and B
        for (int i = 0; i < k; i++) {
            C.sub[i] += A.sub[i];
            C.sub[i] += B.sub[i];
        }

        // Subarrays crossing A and B
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                int rem = (i * j) % k;
                C.sub[rem] += A.suff[i] * B.pref[j];
            }
        }

        return C;
    }

    Node makeNode(int x) {
        Node res;

        x %= k;

        res.prod = x;
        res.pref[x] = 1;
        res.suff[x] = 1;
        res.sub[x] = 1;

        return res;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            tree[p] = makeNode(nums[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(p * 2, l, mid, nums);
        build(p * 2 + 1, mid + 1, r, nums);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            tree[p] = makeNode(val);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(p * 2, l, mid, pos, val);
        else
            update(p * 2 + 1, mid + 1, r, pos, val);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(p * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(p * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(p * 2, l, mid, ql, qr);
        Node right = query(p * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->k = k;
        n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Remaining array = nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            // Each non-empty prefix corresponds to one
            // possible remaining array after removing a suffix.
            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};