void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
    vector<int> t(n + 1);
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        t[pos[x]] = i;  // x这个元素在pos[x]，我们研究下标，所以下标pos[x]在i时刻被删除
    }
    int cur = m;
    deb(a);
    for (int i = 1; i <= n; i++) {
        if (t[i] == 0) {
            cur++;
            t[i] = cur;
        }
    }
    deb(t);
    auto cmpx = [&](array<int, 4>& c, array<int, 4>& d) {
        return c[1] < d[1];
    };
    auto cal = [&](vector<array<int, 4>>& q) {
        vector<int> ans(n + 1);
        Fwk<int> c(n + 1);
        sort(q.begin() + 1, q.end());
        auto cdq = [&](auto self, int l, int r) {
            if (l == r)
                return;
            int mid = (l + r) >> 1;
            self(self, l, mid);
            self(self, mid + 1, r);
            int pl = l, pr = mid + 1;
            while (pl <= mid && pr <= r) {
                if (q[pl][1] < q[pr][1]) {
                    c.add(q[pl][2], 1);
                    pl++;
                } else {
                    ans[q[pr][3]] += c.sum(q[pr][2]);
                    pr++;
                }
            }
            while (pl <= mid) {
                c.add(q[pl][2], 1);
                pl++;
            }
            while (pr <= r) {
                ans[q[pr][3]] += c.sum(q[pr][2]);
                pr++;
            }
            for (int i = l; i <= mid; i++) c.add(q[i][2], -1);
            sort(q.begin() + l, q.begin() + r + 1, cmpx);
        };
        cdq(cdq, 1, n);
        return ans;
    };
    auto re = [&](int x) {
        return n + 1 - x;
    };
    vector<ll> res(n + 2);
    vector<array<int, 4>> q(n + 1);
    for (int i = 1; i <= n; i++) {
        q[i] = {re(t[i]), i, re(a[i]), i};
    }
    auto ans1 = cal(q);
    for (int i = 1; i <= n; i++) res[t[i]] += ans1[i];
    for (int i = 1; i <= n; i++) {
        q[i] = {re(t[i]), re(i), a[i], i};
    }
    auto ans2 = cal(q);
    for (int i = 1; i <= n; i++) res[t[i]] += ans2[i];
    for (int i = n; i >= 1; i--) res[i] += res[i + 1];
    for (int i = 1; i <= m; i++) cout << res[i] << endl;
}