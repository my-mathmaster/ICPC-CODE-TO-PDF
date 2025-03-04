bool iscycle_direct(vector<vector<int>> &e, vector<int> &deg) {//有环返回true
    queue<int> q;
    int n = deg.size() - 1;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (auto v : e[u]) {
            deg[v]--;
            if (deg[v] == 0)
                q.push(v);
        }
    }
    for (int i = 1; i <= n; i++)
        if (deg[i]) {
            return true;
        }
    return false;
}