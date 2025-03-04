bool iscycle_undirect(vector<vector<int>> &e, vector<int> &deg) {  // 有环返回true
    queue<int> q;
    int n = deg.size() - 1;
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1) {
            vis[i] = true;
            q.push(i);
        }
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (auto v : e[u]) {
            deg[v]--;
            if (deg[v] <= 1 && vis[v] == 0) {
                q.push(v);
                vis[v] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] > 1) {  // 最后度数大于1的点在环上
            return true;
        }
    return false;
}//还需要对不同连通块分别处理具体路径和环长度