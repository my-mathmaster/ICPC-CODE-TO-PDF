struct XYL {
    vector<int> vis, match;
    vector<vector<int>> e;
    int n1, n2, m;
    XYL(int n1_, int n2_, int m_) {
        n1 = n1_;
        n2 = n2_;
        m = m_;
        vis.resize(n2 + 1);
        match.resize(n2 + 1);
        e.resize(n1 + 1);
    }
    void addEdge(int u, int v) {
        e[u].emplace_back(v);
    }
    int dfs(int u) {
        for (auto v : e[u]) {
            // 妹子的编号v
            if (vis[v])
                continue;
            vis[v] = 1;  // 先标记这个妹子
            if (!match[v] || dfs(match[v])) {
                match[v] = u;  // 配成对
                return 1;
            }
        }
        return 0;
    }
    int work() {
        int ans = 0;
        for (int i = 1; i <= n1; i++) {
            fill(alls(vis), 0);  // 每轮找增广路以前清空vis
            ans += dfs(i);
        }
        return ans;
    }
    vector<int> fangan() {
        vector<int> res(max(n1, n2) + 1);
        for (int i = 1; i <= n2; i++) res[match[i]] = i;
        return res;  // res[i]表示匹配的女生编号
    };
};