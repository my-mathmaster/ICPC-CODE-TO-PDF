struct Blca {
    struct edge {
        int v = 0, w = 1;
    };
    int n;
    const static int len = __lg(N);
    vector<vector<edge>> e;
    vector<int> dep, dw, sz;
    vector<array<int, len + 1>> st;
    Blca() {};
    Blca(int n) {
        init(n);
    }
    void init(int n1) {
        n = n1;
        e.resize(n + 1);
        dep.resize(n + 1);
        dw.resize(n + 1);
        sz.resize(n + 1);
        st.resize(n + 1);
    }
    void add(int u, int v, int w = 1) {
        e[u].emplace_back(v, w);
    }
    void dfs(int u, int fa) {
        dep[u] = dep[fa] + 1;
        st[u][0] = fa;
        sz[u] = 1;
        for (int i = 1; i <= len; i++) st[u][i] = st[st[u][i - 1]][i - 1];
        for (auto [v, w] : e[u]) {
            deb(u, v);
            if (v == fa)
                continue;
            dw[u] = dw[v] + w;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y])
            swap(x, y);
        for (int i = len; i >= 0; i--) {
            if (dep[st[x][i]] >= dep[y])
                x = st[x][i];
        }
        // 跳到相同深度
        if (x == y)
            return y;
        // 提提前判本身就是祖先关系
        for (int i = len; i >= 0; i--) {
            if (st[x][i] != st[y][i]) {
                x = st[x][i];
                y = st[y][i];
            }
        }
        // 倍增一起向上跳，直到父亲就是答案
        return st[x][0];
    }
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int x, int k) {  // k级祖先
        for (int i = len; i >= 0; i--)
            if ((k >> i) & 1)
                x = st[x][i];
        return x;
    }
};