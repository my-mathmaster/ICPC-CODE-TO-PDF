struct edge {
    int v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> e(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    vector<int> q(m + 1);
    for (int i = 1; i <= m; i++) cin >> q[i];
    //----------------------相关数据
    int mxsz = inf, rt = 0;
    vector<int> sz(n + 1);
    vector<int> d(n + 1);    // 距离
    vector<int> del(n + 1);  // 标记
    vector<int> ans(n + 1);
    map<int, int> have;
    // 求重心函数，每次需要传参数：当前剩余点数sum
    // 每次使用getroot以前要初始化mxsz
    auto getroot = [&](auto self, int u, int fa, int sum) -> void {
        sz[u] = 1;
        int tmp = 0;
        for (auto [v, w] : e[u]) {
            if (v == fa || del[v])
                continue;
            self(self, v, u, sum);
            sz[u] += sz[v];
            tmp = max(tmp, sz[v]);
        }
        tmp = max(tmp, sum - sz[u]);
        if (tmp < mxsz) {
            mxsz = tmp;
            rt = u;
        }
    };
    auto upd = [&](auto self, int u, int fa, vector<int>& tmp) -> void {
        tmp.push_back(d[u]);
        for (auto [v, w] : e[u]) {
            if (v == fa || del[v])
                continue;
            d[v] = d[u] + w;
            self(self, v, u, tmp);
        }
    };
    auto cal = [&](int u) -> void {  // 计算经过u的答案
        have[0] = 1;
        vector<int> alltmp;
        for (auto [v, w] : e[u]) {
            if (del[v])
                continue;
            d[v] = w;
            vector<int> tmp;
            upd(upd, v, u, tmp);
            // 更新答案
            for (auto ndis : tmp) {
                for (int k = 1; k <= m; k++) {
                    if (q[k] >= ndis) {
                        if (have.count(q[k] - ndis)) {
                            ans[k] = 1;
                        }
                    }
                }
            }
            // 更新have
            for (auto ndis : tmp) {
                if (ndis <= inf) {  // 这里的距离带边权
                    alltmp.push_back(ndis);
                    have[ndis] = 1;
                }
            }
        }
        // 及时清空这一次的计算，未来还要用
        for (auto x : alltmp) have.erase(x);
    };
    // 分治
    auto divide = [&](auto self, int u) -> void {
        cal(u);
        del[u] = 1;
        for (auto [v, w] : e[u]) {
            if (del[v])
                continue;
            mxsz = sz[v];                  // 分治递归下去
            getroot(getroot, v, v, mxsz);  // 找到新的递归重心
            self(self, rt);
        }
    };
    //-------------------------具体调用
    mxsz = n;
    getroot(getroot, 1, 1, n);    // rt更新
    getroot(getroot, rt, rt, n);  // 重构sz[]
    divide(divide, rt);
    // 输出
    for (int i = 1; i <= m; i++) {
        if (ans[i])
            cout << "AYE" << endl;
        else
            cout << "NAY" << endl;
    }
}