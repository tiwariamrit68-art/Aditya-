class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;

        return true;
    }
};

class Solution {
public:
    bool canBuild(int n, vector<vector<int>>& edges, int k, long long target) {

        DSU dsu(n);

        // ------------------------------------------------
        // Step 1: Add all mandatory edges.
        // ------------------------------------------------
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            long long s = e[2];
            int must = e[3];

            if (must == 1) {

                // Mandatory edge cannot be upgraded.
                if (s < target)
                    return false;

                // Mandatory edges must not form a cycle.
                if (!dsu.unite(u, v))
                    return false;
            }
        }

        // ------------------------------------------------
        // Step 2: Add optional edges that already satisfy
        // target without upgrading.
        // ------------------------------------------------
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            long long s = e[2];
            int must = e[3];

            if (must == 0 && s >= target) {
                dsu.unite(u, v);
            }
        }

        // ------------------------------------------------
        // Step 3: Use optional edges requiring upgrades.
        // ------------------------------------------------
        int upgrades = 0;

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            long long s = e[2];
            int must = e[3];

            if (must == 0 &&
                s < target &&
                2 * s >= target) {

                if (dsu.unite(u, v)) {
                    upgrades++;

                    if (upgrades > k)
                        return false;
                }
            }
        }

        // ------------------------------------------------
        // Step 4: Check whether all nodes are connected.
        // ------------------------------------------------
        int root = dsu.find(0);

        for (int i = 1; i < n; i++) {
            if (dsu.find(i) != root)
                return false;
        }

        return true;
    }

    long long maxStability(int n, vector<vector<int>>& edges, int k) {

        long long lo = 1;
        long long hi = 200000; // 2 * max strength
        long long ans = -1;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;

            if (canBuild(n, edges, k, mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};