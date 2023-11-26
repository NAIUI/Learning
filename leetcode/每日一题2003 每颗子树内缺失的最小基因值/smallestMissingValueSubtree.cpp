class Solution {
public:
    vector<int> smallestMissingValueSubtree(vector<int> &parents, vector<int> &nums) {
        int n = parents.size();
        vector<int> ans(n, 1);
        auto it = find(nums.begin(), nums.end(), 1);
        if (it == nums.end()) { // 不存在基因值为 1 的点
            return ans;
        }

        // 建树
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            g[parents[i]].push_back(i);
        }

        unordered_set<int> vis;
        function<void(int)> dfs = [&](int x) -> void {
            vis.insert(nums[x]); // 标记基因值
            for (int son: g[x]) {
                if (!vis.count(nums[son])) {
                    dfs(son);
                }
            }
        };

        int mex = 2; // 缺失的最小基因值
        int node = it - nums.begin();
        while (node >= 0) {
            dfs(node);
            while (vis.count(mex)) { // node 子树包含这个基因值
                mex++;
            }
            ans[node] = mex; // 缺失的最小基因值
            node = parents[node]; // 往上走
        }
        return ans;
    }
};