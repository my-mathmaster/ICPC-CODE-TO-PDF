void get_cycle(const vector<vector<int>>& e, vector<vector<int>>& cycle) {
    int n = e.size() - 1;//适用于每个点只在一个环上的情况，不考虑环套环
    vector<int> vis(n + 1), pre(n + 1);

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        vis[u] = 1;  // 标记当前节点正在访问
        for (auto v : e[u]) {
            if (v == fa)  // 无向图中跳过父节点
                continue;
            deb(u, v);
            if (vis[v] == 0) {         // 未访问过的节点
                pre[v] = u;            // 记录前驱节点
                self(self, v, u);      // 递归访问
            } else if (vis[v] == 1) {  // 找到一个环
                vector<int> temp;
                int tmp = u;
                while (tmp != v) {  // 回溯找到环中的节点
                    temp.push_back(tmp);
                    tmp = pre[tmp];
                }
                temp.push_back(v);
                cycle.push_back(temp);  // 将环存入cycle
            }
        }
        vis[u] = 2;  // 标记为已访问
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {  // 对每个未访问节点进行 DFS
            dfs(dfs, i, 0);
        }
    }
}
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> e(n + 1), cycle(n + 1);
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    get_cycle(e, cycle);
    for (int i = 0; i < (int)cycle.size(); i++) {
        if (cycle[i].size()) {
            sort(alls(cycle[i]));//不排序才是环上正确的路径
            for (auto x : cycle[i]) cout << x << " ";
            cout << endl;
        }
    }
}