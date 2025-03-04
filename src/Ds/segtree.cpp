template <class Info>
struct Segtree {
#define ls(x) x << 1
#define rs(x) (x << 1) | 1
    int n;
    vector<Info> info;
    Segtree() : n(0) {}
    Segtree(int n_, Info v_ = Info()) { init(vector<Info>(n_ + 1, v_)); }
    Segtree(vector<Info> t_) { init(t_); }
    void init(vector<Info> a)  //[1,n]
    {
        n = a.size() - 1;
        info.assign((n << 2) + 1, Info());
        function<void(int, int, int)> build = [&](int x, int l, int r) -> void {
            if (l == r) {
                info[x] = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(ls(x), l, mid);
            1 build(rs(x), mid + 1, r);
            pushup(x);
        };
        build(1, 1, n);
    }
    void pushup(int x) { info[x] = info[ls(x)] + info[rs(x)]; }
    void update(int x, int l, int r, int p, const Info& v) {
        if (l == r) {
            info[x] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            update(ls(x), l, mid, p, v);
        else
            update(rs(x), mid + 1, r, p, v);
        pushup(x);
    }
    void update(int p, const Info& v) { update(1, 1, n, p, v); }
    Info query(int x, int l, int r, int ql, int qr) {
        if (l > qr || r < ql)
            return Info();
        if (ql <= l && r <= qr)
            return info[x];
        int mid = (l + r) >> 1;
        return query(ls(x), l, mid, ql, qr) +
               query(rs(x), mid + 1, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 1, n, ql, qr); }
    template <class F>
    int findFirst(int x, int l, int r, int ql, int qr, F pred) {
        if (l > qr || r < ql || !pred(info[x]))
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int res = findFirst(x << 1, l, mid, ql, qr, pred);
        if (res == -1)
            res = findFirst(x << 1 | 1, mid + 1, r, ql, qr, pred);
        return res;
    }
    template <class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 1, n, l, r, pred);
    }
    template <class F>
    int findLast(int x, int l, int r, int ql, int qr, F pred) {
        if (l > qr || r < ql || !pred(info[x]))
            return -1;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        int res = findLast(x << 1 | 1, mid + 1, r, ql, qr, pred);
        if (res == -1)
            res = findLast(x << 1, l, mid, ql, qr, pred);
        return res;
    }
    template <class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 1, n, l, r, pred);
    }
};
struct Info {
    ll sum = 0, len = 1;
};
Info operator+(const Info& a, const Info& b) {  // 维护的信息怎么合并
    Info c = Info();
    c.sum = a.sum + b.sum;
    c.len = a.len + b.len;
    return c;
};