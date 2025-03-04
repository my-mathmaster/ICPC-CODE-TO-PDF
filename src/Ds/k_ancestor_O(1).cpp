void solve() {
    int n, q;
    cin >> n >> q;
    int rt = 0;
    vector<int> l(n + 1), r(n + 1), node(n + 1);
    int idx = 0;
    vector<int> fa(n + 1), dep(n + 1);
    vector<int> hson(n + 1), top(n + 1), len(n + 1);
    vector<vector<int>> e(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x == 0) {
            rt = i;
            continue;
        }
        e[x].push_back(i);
    }
    auto dfs1 = [&](auto self, int u, int curd = 1) -> void {
        dep[u] = curd;
        len[u] = 1;
        for (auto v : e[u]) {
            fa[v] = u;
            self(self, v, curd + 1);
            if (len[v] + 1 > len[u]) {
                hson[u] = v;
                len[u] = len[v] + 1;
            }
        }
    };
    auto dfs2 = [&](auto self, int u, int tp) -> void {
        l[u] = ++idx;
        node[idx] = u;
        top[u] = tp;
        if (hson[u])
            self(self, hson[u], tp);
        for (auto v : e[u]) {
            if (top[v])
                continue;
            self(self, v, v);
        }
        r[u] = idx;
    };
    int bei = __lg(n);
    vector<vector<int>> st(bei + 1, vector<int>(n + 1));
    vector<vector<int>> anc(n + 1), des(n + 1);
    auto work = [&](int rt) {
        dfs1(dfs1, rt);
        dfs2(dfs2, rt, rt);
        for (int i = 1; i <= n; i++) st[0][i] = fa[i];
        for (int i = 1; i <= bei; ++i) {
            for (int j = 1; j <= n; ++j) {
                st[i][j] = st[i - 1][st[i - 1][j]];
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (top[i] == i) {
                for (int j = 0, p = i; j < len[i]; ++j, p = fa[p])
                    anc[i].push_back(p);
                for (int j = 0; j < len[i]; ++j)
                    des[i].push_back(node[l[i] + j]);
            }
        }
    };
    auto query = [&](int p, int k) {
        if (k == 0)
            return p;  // 特判
        int i = __lg(k), q = st[i][p];
        int tp = top[q];
        // q的k-(1<<i)级祖先小于链长，预处理了两倍链长的信息
        int d = k - (1 << i) - (dep[q] - dep[tp]);
        if (d > 0)
            return anc[tp][d];
        else
            return des[tp][-d];
    };

    for (int i = 1; i <= q; i++) {
        int x, k;
        cin >> x >> k;
        int res = query(x, k);
        cout << res << endl;
    }
}
