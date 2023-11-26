class Solution {
public:
    int maximumInvitations(vector<int> &favorite) {
        int n = favorite.size();
        vector<int> deg(n);
        for (int f: favorite) {
            deg[f]++; // 统计基环树每个节点的入度
        }

        vector<vector<int>> rg(n); // 反图
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) { // 拓扑排序，剪掉图上所有树枝
            int x = q.front();
            q.pop();
            int y = favorite[x]; // x 只有一条出边
            rg[y].push_back(x);
            if (--deg[y] == 0) {
                q.push(y);
            }
        }

        // 通过反图 rg 寻找树枝上最深的链
        function<int(int)> rdfs = [&](int x) -> int {
            int max_depth = 1;
            for (int son: rg[x]) {
                max_depth = max(max_depth, rdfs(son) + 1);
            }
            return max_depth;
        };

        int max_ring_size = 0, sum_chain_size = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0) continue;

            // 遍历基环上的点
            deg[i] = 0; // 将基环上的点的入度标记为 0，避免重复访问
            int ring_size = 1; // 基环长度
            for (int x = favorite[i]; x != i; x = favorite[x]) {
                deg[x] = 0; // 将基环上的点的入度标记为 0，避免重复访问
                ring_size++;
            }

            if (ring_size == 2) { // 基环长度为 2
                sum_chain_size += rdfs(i) + rdfs(favorite[i]); // 累加两条最长链的长度
            } else {
                max_ring_size = max(max_ring_size, ring_size); // 取所有基环长度的最大值
            }
        }
        return max(max_ring_size, sum_chain_size);
    }
};