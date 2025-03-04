template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
    int n;
    vector<vector<T>> st;
    F func;

    SparseTable(const vector<T>& a, const F& f) : func(f) {
        n = (int)a.size() - 1;
        int max_log = __lg(n) + 1;
        st.resize(max_log + 1);
        st[0] = a;
        for (int j = 1; j <= max_log; j++) {
            st[j].resize(n + 1);
            for (int i = 1; i + (1 << (j - 1)) <= n; i++) {
                st[j][i] = func(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T get(int l, int r) const {
        int len = __lg(r - l + 1);
        return func(st[len][l], st[len][r - (1 << len) + 1]);
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    SparseTable<int> qmx(a, [](int i, int j) { return max(i, j); });
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        cout << qmx.get(l, r) << endl;
    }
}
