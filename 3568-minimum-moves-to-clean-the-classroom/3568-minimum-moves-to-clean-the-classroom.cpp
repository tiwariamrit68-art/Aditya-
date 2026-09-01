
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int,int>> litter;

        // Find start and all litter cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        // No litter to collect
        if (k == 0) return 0;

        // Map litter position -> bit index
        vector<vector<int>> id(m, vector<int>(n, -1));
        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            visited[r][c][e][mask]

            energy can be 0...energy
            mask can be 0...(2^k - 1)
        */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << k, false)
                )
            )
        );

        struct State {
            int r, c, e, mask, dist;
        };

        queue<State> q;

        visited[sr][sc][energy][0] = true;
        q.push({sr, sc, energy, 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, e, mask, dist] = q.front();
            q.pop();

            if (mask == fullMask)
                return dist;

            // If energy is 0, no movement is possible.
            if (e == 0)
                continue;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                if (classroom[nr][nc] == 'X')
                    continue;

                int ne = e - 1;
                int nmask = mask;

                // Collect litter
                if (classroom[nr][nc] == 'L') {
                    int idx = id[nr][nc];
                    nmask |= (1 << idx);
                }

                // Reset energy on R
                if (classroom[nr][nc] == 'R') {
                    ne = energy;
                }

                if (!visited[nr][nc][ne][nmask]) {
                    visited[nr][nc][ne][nmask] = true;
                    q.push({nr, nc, ne, nmask, dist + 1});
                }
            }
        }

        return -1;
    }
};