struct edge {
    int v, w;
};
struct HLD {
    int n;
    vector<int> siz, top, parent, l, r, hson, dep;
    vector<vector<edge>> adj;
    int idx;
    vector<int> mn;  // 1-u的最小边权

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
        mn.resize(n + 1, 1e9);
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
            mn[v] = min(mn[u], w);
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
void solve() {
    int n;
    cin >> n;
    HLD hld(n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        hld.addEdge(u, v, w);
        hld.addEdge(v, u, w);
    }
    auto cmp = [&](int i, int j) {
        return hld.l[i] < hld.l[j];
    };
    hld.work(1);
    auto buildvt = [&](vector<int>& node, vector<vector<edge>>& e) {
        node.push_back(1);  // 保证根节点在虚树中存在
        sort(alls(node), cmp);
        node.erase(unique(alls(node)), node.end());
        set<int> tmp;
        for (auto x : node) tmp.insert(x);
        for (int i = 1; i < (int)node.size(); i++) tmp.insert(hld.lca(node[i - 1], node[i]));
        node.clear();
        for (auto x : tmp) node.push_back(x);
        sort(alls(node), cmp);
        vector<int> st;  // 维护一个栈
        for (auto v : node) {
            while (!st.empty() && !hld.isAncester(st.back(), v))
                st.pop_back();
            if (!st.empty())
                e[st.back()].push_back({v, hld.mn[v]});
            st.push_back(v);
        }
    };
    int q;
    cin >> q;
    vector<vector<edge>> e(n + 1);
    vector<ll> dp(n + 1);  // 使得u子树内关键点与u不连通的代价
    vector<bool> vis(n + 1);
    auto cal = [&](auto self, int u, int fa) -> void {  // 计算答案
        for (auto [v, w] : e[u]) {
            if (v == fa)
                continue;
            self(self, v, u);
            if (vis[v])
                dp[u] += w;
            else
                dp[u] += min((ll)w, dp[v]);
        }
    };
    auto clear = [&](vector<int>& node) {  // 清空本次用的点的信息
        for (auto x : node) {
            vis[x] = 0;
            dp[x] = 0;
            e[x].clear();
        }
    };
    for (int i = 1; i <= q; i++) {
        int num;
        cin >> num;
        vector<int> node;
        for (int j = 1; j <= num; j++) {
            int x;
            cin >> x;
            node.push_back(x);
            vis[x] = 1;
        }
        buildvt(node, e);
        cal(cal, 1, 1);
        cout << dp[1] << endl;
        clear(node);
    }
}