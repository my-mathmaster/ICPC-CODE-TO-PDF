struct edge {
    int v, w;
};
struct HLD {
    int n;
    vector<int> siz, top, parent, l, r, hson, dep;
    vector<vector<edge>> adj;
    int idx;
    // 加数据结构
    vector<int> a;
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
        a.resize(n + 1);
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    void work(auto& plb, int root = 1) {
        top[root] = root;
        dep[root] = 1;
        dfs1(root, 0, plb);
        dfs2(root, root);
    }
    void dfs1(int u, int f, auto& plb) {  // 搞fa,dep,son
        siz[u] = 1;
        plb.insert(a[u], u, f, *this);  // 继承父节点，插入当前节点
        for (auto [v, w] : adj[u]) {
            if (v == f)
                continue;
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v, u, plb);
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
struct prelinerbasis_tree {
    static const int mxl = 60;
    vector<array<int, mxl + 1>> p;    // p[id][i]表示前id个数，第i位的线性基
    vector<array<int, mxl + 1>> pos;  // pos[id][i]表示构造基p[id][i]的元素的下标最大值
    prelinerbasis_tree() {}
    prelinerbasis_tree(int n) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        pos.resize(n + 1);
    }
    void insert(int x, int u, int f, auto& hld) {
        deb(x, u, f);
        for (int i = 0; i <= mxl; i++)  // 复制父版
            p[u][i] = p[f][i], pos[u][i] = pos[f][i];
        int cur = u;
        for (int i = mxl; i >= 0; --i) {
            if ((x >> i) & 1) {
                deb(x, i);
                if (!p[u][i]) {  // 不存在则加入
                    p[u][i] = x;
                    pos[u][i] = cur;
                    break;
                }
                // 存在则先交换，后异或
                if (hld.dep[pos[u][i]] < hld.dep[cur])
                    swap(x, p[u][i]), swap(pos[u][i], cur);
                x ^= p[u][i];
            }
        }
    }
    int querymx(const vector<int>& b, int x = 0) {
        int res = x;
        for (int i = mxl; i >= 0; i--) res = max(res, res ^ b[i]);
        return res;
    }
    vector<int> query(int x, int y, auto& hld) {  // 查询x到y简单路径构造的线性基
        int tmplca = hld.lca(x, y);
        deb(x, y, tmplca);
        vector<int> b(mxl + 1);
        for (int i = mxl; i >= 0; --i) {  // 从x到根的链中提取出x~lca的线性基
            if (hld.dep[pos[x][i]] >= hld.dep[tmplca])
                b[i] = p[x][i];
        }
        for (int i = mxl; i >= 0; --i) {  // 暴力合并y-lca的基
            if (hld.dep[pos[y][i]] < hld.dep[tmplca])
                continue;
            int x = p[y][i];  // 提取y~lca链的基
            for (int j = i; j >= 0; --j) {
                if (x >> j & 1) {
                    if (!b[j]) {
                        b[j] = x;
                        break;
                    }
                    x ^= b[j];
                }
            }
        }
        return b;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    HLD hld(n);
    prelinerbasis_tree plb(n);
    for (int i = 1; i <= n; i++) cin >> hld.a[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.addEdge(u, v, 1);
        hld.addEdge(v, u, 1);
    }
    hld.work(plb, 1);
    for (int i = 1; i <= n; i++) deb(i, hld.dep[i]);
    for (int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;
        auto b = plb.query(u, v, hld);
        deb(b);
        cout << plb.querymx(b) << endl;
    }
}