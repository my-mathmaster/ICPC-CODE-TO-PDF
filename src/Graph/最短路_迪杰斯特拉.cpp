struct edge {
    int v, w;
};
vector<int> dijs(vector<vector<edge>>& e, int s) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    vector<int> d(n + 1, (1LL<<31)-1);
    vector<bool> vis(n + 1);
    d[s] = 0;
    q.push({d[s],s});
    while (q.size()) {
        auto t = q.top();
        q.pop();
        int u = t.sec;
        if (vis[u])
            continue;  // 再进队就直接跳过
        vis[u] = 1;    // 标记u已出队
        
        for (auto [v, w] : e[u]) {
            
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.push({d[v], v});  // 小根堆
            }
        }
        
    }
    return d;
}