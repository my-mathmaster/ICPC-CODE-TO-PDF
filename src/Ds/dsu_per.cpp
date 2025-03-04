struct DSU {
    vector<int> siz;
    vector<int> f;
    vector<array<int, 2>> his;

    DSU(int n) : siz(n + 1, 1), f(n + 1) {
        iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int time() {
        return his.size();
    }

    void revert(int tm) {
        while ((int)his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }
    void backlast() {
        assert(his.size());
        // if (his.size() == 0)
        //     return;
        revert(his.size() - 1);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(m + 1);
    DSU dsu(n);
    vector<array<int, 3>> type(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> type[i][0];
        if (type[i][0] == 1 || type[i][0] == 3) {
            e[i - 1].push_back(i);
            cin >> type[i][1] >> type[i][2];
        } else {
            int k;
            cin >> k;
            assert(k < i);
            e[k].push_back(i);
        }
    }
    vector<int> ans(m + 1);
    function<void(int)> dfs = [&](int u) {
        int tmp = dsu.time();

        for (auto v : e[u]) {
            // int tmp = dsu.time();
            auto [op, x, y] = type[v];
            bool flag = 0;
            if (op == 1)
                flag = dsu.merge(x, y);  // 必须合并成功才能在下面撤销
            else if (op == 3)
                ans[v] = (dsu.find(x) == dsu.find(y)) ? 1 : 0;
            dfs(v);
            // dsu.revert(tmp);
            if (op == 1 && flag)
                dsu.backlast();
        }
    };
    dfs(0);
    for (int i = 1; i <= m; i++) {
        if (type[i][0] == 3) {
            deb(i);
            cout << ans[i] << endl;
        }
    }
}