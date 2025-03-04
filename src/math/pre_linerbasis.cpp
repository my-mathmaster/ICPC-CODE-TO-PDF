struct prelinerbasis {
    static const int mxl = 20;
    vector<array<int, mxl + 1>> p;    // p[id][i]表示前id个数，第i位的线性基
    vector<array<int, mxl + 1>> pos;  // pos[id][i]表示构造基p[id][i]的元素的下标最大值
    prelinerbasis() {}
    prelinerbasis(int n) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        pos.resize(n + 1);
    }
    void insert(int x, int id) {
        for (int i = 0; i <= mxl; i++) {  // 复制前一版
            p[id][i] = p[id - 1][i];
            pos[id][i] = pos[id - 1][i];
        }
        int cur = id;
        for (int i = mxl; i >= 0; i--) {
            if (x >> i & 1) {
                if (!p[id][i]) {  // 不存在则加入
                    p[id][i] = x;
                    pos[id][i] = cur;
                    break;
                }
                // 存在则先交换，后异或
                if (pos[id][i] < cur)
                    swap(p[id][i], x), swap(pos[id][i], cur);
                x ^= p[id][i];
            }
        }
    }
    int query(int l, int r, int x = 0) {  //[l,r]的线性基与x异或的最大值
        int ans = x;
        for (int i = mxl; i >= 0; i--)
            if (pos[r][i] >= l)
                ans = max(ans, ans ^ p[r][i]);
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    prelinerbasis plb(n);
    for (int i = 1; i <= n; i++) plb.insert(a[i], i);
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        cout << plb.query(l, r) << endl;
    }
}