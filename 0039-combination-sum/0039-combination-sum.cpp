class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void dfs(int idx, int target, vector<int>& candidates) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        if (idx == candidates.size() || target < 0)
            return;

        // Take current candidate (can reuse it)
        path.push_back(candidates[idx]);
        dfs(idx, target - candidates[idx], candidates);
        path.pop_back();

        // Skip current candidate
        dfs(idx + 1, target, candidates);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(0, target, candidates);
        return ans;
    }
};