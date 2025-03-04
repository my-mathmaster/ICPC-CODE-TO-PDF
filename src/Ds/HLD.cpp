struct HLD {
    int n;
    vector<int> siz, top, dep, parent, l, r, hson, seq;
    vector<vector<int>> adj;
    int idx;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        parent.resize(n + 1);
        l.resize(n + 1);
        r.resize(n + 1);
        hson.resize(n + 1);
        seq.resize(n + 1);
        idx = 0;
        adj.assign(n + 1, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void work(int root = 1) {
        top[root] = root;
        dep[root] = 1;
        parent[root] = -1;
        dfs1(root, -1);
        dfs2(root, root);
    }
    void dfs1(int u, int f) {  // 搞fa,dep,son
        if (parent[u] != -1) {
            adj[u].erase(find(alls(adj[u]), parent[u]));
        }
        siz[u] = 1;
        for (int v : adj[u]) {
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
        l[u] = idx++;
        seq[l[u]] = u;
        if (!hson[u])
            return;        // 无重儿子
        dfs2(hson[u], t);  // 搜重儿子
        for (int v : adj[u]) {
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

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }

        int d = dep[u] - k;  // 目标节点的深度

        while (dep[top[u]] > d) {  // 不在当前链上
            u = parent[top[u]];    // 跳链头的父亲
        }
        // 同一条链上dfs序连续
        return seq[l[u] - dep[u] + d];
    }

    bool isAncester(int u, int v) {  // 判断u是不是v的祖先
        return l[u] <= l[v] && l[v] < r[u];
    }

    int rootedParent(int u, int v) {  // u为根的时候，v的父亲节点
        swap(u, v);
        if (u == v) {
            return u;
        }
        // v为根的时候，u的父亲节点
        if (!isAncester(u, v)) {  // u不是v的祖先
            return parent[u];
        }
        // u是v的祖先。现在v为根，u的父亲是(dfs序>=v)的那个节点
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return l[x] < l[y];
        });
        it--;  // 找到第最后一个小于vd的dfs序节点
        return *it;
    }

    int rootedSize(int u, int v) {  // u为根的时候，v的子树大小
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {  // 如果v不是u的祖先
            return siz[v];
        }
        // v是u祖先。找到u为根的时候v的父亲。总数减去包含u的那部分
        return n - siz[rootedParent(u, v)];
    }

    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};