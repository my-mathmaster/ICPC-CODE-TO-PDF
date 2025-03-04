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
        while (his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n + 1);
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {//合并x,y
            int x, y;
            cin >> x >> y;
            dsu.merge(x, y);
        } else if (op == 2)//撤回上一次操作
            dsu.revert(dsu.his.size() - 1);
        else {
            int x, y;
            cin >> x >> y;//查询x,y连通性
            if (dsu.find(x) == dsu.find(y))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}
