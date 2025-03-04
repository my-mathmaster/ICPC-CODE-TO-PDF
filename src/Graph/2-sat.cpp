struct TwoSat {
    int n;
    vector<vector<int>> e;
    vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}
    void add(int u, bool f, int v, bool g) {
        // 偶数是u取反的变量，奇数是正变量
        // 一般来说需要反变量向正变量连边。
        e[2 * u + !f].push_back(2 * v + g);
        if (u == v)
            return;  // 对于单变量指定特判
        e[2 * v + !g].push_back(2 * u + f);
    }
    bool judge() {
        vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        vector<int> stk;
        int now = 0, cnt = 0;
        function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i)
            if (dfn[i] == -1)
                tarjan(i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1])
                return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    vector<bool> answer() { return ans; }
};
void solve() {
    int n, m;
    cin >> n >> m;
    TwoSat sat2(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        bool f1, f2;
        //u为f1或v为f2
        cin >> u >> f1 >> v >> f2;
        u--;
        v--;
        sat2.add(u, f1, v, f2);
    }
    if (sat2.judge()) {
        cout << "POSSIBLE" << endl;
        for (int i = 0; i < n; i++) cout << sat2.ans[i] << " ";
    } else
        cout << "IMPOSSIBLE" << endl;
}
