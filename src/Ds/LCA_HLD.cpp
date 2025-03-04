struct edge {
    int v, w;
};
struct HLD {
    int n;
    vector<int> siz, top, parent, l, r, hson, dep;
    vector<vector<edge>> adj;
    int idx;
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n + 1), hson.resize(n + 1), top.resize(n + 1);
        parent.resize(n + 1);
        l.resize(n + 1), r.resize(n + 1);
        idx = 0;
        adj.resize(n + 1), dep.resize(n + 1);
        // 根据题目要求加数据结构
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    void work(int root = 1) {
        top[root] = root;
        parent[root] = -1;
        dep[root] = 1;
        dfs1(root, -1);
        dfs2(root, root);
    }
    void dfs1(int u, int f) {  // 搞fa,dep,son
        siz[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (v == f)
                continue;
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[hson[u]] < siz[v])
                hson[u] = v;
        }
    }
    void dfs2(int u, int t) {  // 搞top
        top[u] = t;            // 记录链头
        l[u] = ++idx;
        if (!hson[u]) {
            r[u] = idx;
            return;
        }  // 无重儿子
        dfs2(hson[u], t);  // 搜重儿子
        for (auto [v, w] : adj[u]) {
            if (v == parent[u] || v == hson[u])
                continue;
            dfs2(v, v);  // 搜轻儿子
        }
        r[u] = idx;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    bool isAncester(int u, int v) {  // 判断u是不是v的祖先
        return l[u] <= l[v] && r[v] <= r[u];
    }
};