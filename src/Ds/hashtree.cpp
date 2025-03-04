struct treehash {
    int n;
    int rt = 0;
    vector<ll> h1, h2;
    vector<int> siz;
    vector<vector<int>> e;
    treehash(int n_) : n(n_), h1(n_ + 1), h2(n_ + 1), siz(n_ + 1), e(n_ + 1) {}
    ll h(ll x) {
#pragma GCC diagnostic ignored "-Woverflow"
        return x * x * x * 1237123 + 19260817;
    }

    ll f(ll x) {
        ll cur = h(x & ((1 << 31) - 1)) + h(x >> 31);
        return cur;
    }
    void add(int u, int v) {
        e[u].push_back(v);
    }
    int pos = 0, pos2 = 0, ans = 1e9;
    void getroot(int u, int fa) {
        siz[u] = 1;
        int mx = 0;
        for (auto v : e[u]) {
            if (v == fa)
                continue;
            getroot(v, u);
            siz[u] += siz[v];
            mx = max(mx, siz[v]);
        }
        mx = max(mx, n - siz[u]);
        // 维护了重心是pos
        if (mx < ans) {
            ans = mx, pos = u, pos2 = 0;
        } else if (mx == ans) {
            pos2 = u;
        }
    };
    void dfs1(int u, int fa, auto &h) {
        h[u] = 1;
        for (auto v : e[u]) {
            if (v == fa)
                continue;
            dfs1(v, u, h);
            h[u] += f(h[v]);
        }
    };
    int work() {
        getroot(rt, 0);
        dfs1(pos, 0, h1);
        if (pos2)
            dfs1(pos2, 0, h2);
        ll val = h1[pos];
        if (pos2) {
            val = max(val, h2[pos2]);
        }
        return val;
    }
};
//m颗无根无标号，n个节点的树。两个哈希值取最大的那个作为key
void solve() {
    map<ll, int> mp;
    int n, m;
    cin >> m;
    for (int j = 1; j <= m; j++) {
        cin >> n;
        treehash th(n);
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x == 0)
                th.rt = i;
            else
                th.add(i, x), th.add(x, i);
        }
        ll val = th.work();
        if (mp.count(val) == 0)
            mp[val] = j;
        cout << mp[val] << endl;
    }
}