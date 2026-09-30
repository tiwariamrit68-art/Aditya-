class Solution {
public:
    vector<vector<string>> ans;
    vector<string> board;
    vector<int> col, diag1, diag2;

    void solve(int row, int n) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int c = 0; c < n; c++) {
            // Check column and diagonals
            if (col[c] || diag1[row - c + n - 1] || diag2[row + c])
                continue;

            // Place queen
            board[row][c] = 'Q';
            col[c] = 1;
            diag1[row - c + n - 1] = 1;
            diag2[row + c] = 1;

            solve(row + 1, n);

            // Backtrack
            board[row][c] = '.';
            col[c] = 0;
            diag1[row - c + n - 1] = 0;
            diag2[row + c] = 0;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        board = vector<string>(n, string(n, '.'));

        col.resize(n, 0);
        diag1.resize(2 * n - 1, 0);
        diag2.resize(2 * n - 1, 0);

        solve(0, n);

        return ans;
    }
};