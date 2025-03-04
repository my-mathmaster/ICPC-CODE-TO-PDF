struct LcaRmq {
    int n;
    vector<vector<int>> &adj;
    int root, tot;
    vector<int> dfn, ol, lg2, dep;
    vector<vector<int>> st;
    LcaRmq(int n_, auto &g_, auto r = 1) : n(n_), adj(g_), root(r) {
        ol.resize(n << 1);
        dfn.resize(n + 1);
        dep.resize(n + 1);
        lg2.resize(n << 1);
        tot = 0;
        auto dfs = [&](int x, int fa, auto dfs) -> void {
            ol[++tot] = x;
            dfn[x] = tot;
            dep[x] = dep[fa] + 1;
            for (auto y : adj[x]) {
                if (y == fa)
                    continue;
                dfs(y, x, dfs);
                ol[++tot] = x;
            }
        };
        dfs(root, 0, dfs);
        lg2[0] = -1;
        for (int i = 1; i <= tot; i++) lg2[i] = lg2[i >> 1] + 1;
        st.assign(lg2[tot] + 1, vector<int>(n * 2, 0));
        for (int i = 1; i <= tot; i++) st[0][i] = ol[i];
        for (int j = 1; j <= lg2[tot]; j++) {
            for (int i = 1; i + (1 << j) - 1 <= tot; i++) {
                st[j][i] = dep[st[j - 1][i]] < dep[st[j - 1][i + (1 << (j - 1))]]
                               ? st[j - 1][i]
                               : st[j - 1][i + (1 << (j - 1))];
            }
        }
    }
    int lca(int u, int v) {
        u = dfn[u], v = dfn[v];
        if (u > v)
            swap(u, v);
        int d = lg2[v - u + 1];
        return dep[st[d][u]] < dep[st[d][v - (1 << d) + 1]]
                   ? st[d][u]
                   : st[d][v - (1 << d) + 1];
    }
};