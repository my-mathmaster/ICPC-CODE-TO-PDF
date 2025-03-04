template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) { init(vector<Info>(n_ + 1, v_)); }
    LazySegmentTree(vector<Info> t_) { init(t_); }
    void init(vector<Info> a)  //[1,n]
    {
        n = a.size() - 1;
        info.assign((n << 2) + 1, Info());
        tag.assign((n << 2) + 1, Tag());
        function<void(int, int, int)> build = [&](int x, int l, int r) -> void {
            if (l == r) {
                info[x] = a[l];
                return;
            }
            int mid = l + r >> 1;
            build(x << 1, l, mid);
            build(x << 1 | 1, mid + 1, r);
            pushup(x);
        };
        build(1, 1, n);
    }
    void pushup(int x) { info[x] = info[x << 1] + info[x << 1 | 1]; }
    void apply(int p, const Tag& v) {
        info[p].apply(v);  // 标记更新自己
        tag[p].apply(v);   // 下传标记
    }
    void pushdown(int x) {
        apply(x << 1, tag[x]);
        apply(x << 1 | 1, tag[x]);
        tag[x] = Tag();
    }
    void update(int x, int l, int r, int p, const Info& v) {
        if (l == r) {
            info[x] = v;
            return;
        }
        int mid = l + r >> 1;
        pushdown(x);
        if (p <= mid)
            update(x << 1, l, mid, p, v);
        else
            update(x << 1 | 1, mid + 1, r, p, v);
        pushup(x);
    }
    void update(int p, const Info& v) { update(1, 1, n, p, v); }
    Info query(int x, int l, int r, int ql, int qr) {
        if (l > qr || r < ql)
            return Info();
        if (ql <= l && r <= qr)
            return info[x];
        int mid = l + r >> 1;
        pushdown(x);
        return query(x << 1, l, mid, ql, qr) +
               query(x << 1 | 1, mid + 1, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 1, n, ql, qr); }
    void rangeupdate(int x, int l, int r, int ql, int qr, const Tag& v) {
        if (l > qr || r < ql)
            return;
        if (ql <= l && r <= qr) {
            apply(x, v);
            return;
        }
        int mid = l + r >> 1;
        pushdown(x);
        rangeupdate(x << 1, l, mid, ql, qr, v);
        rangeupdate(x << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(x);
    }
    void rangeupdate(int ql, int qr, const Tag& v) {
        rangeupdate(1, 1, n, ql, qr, v);
    }
    template <class F>
    int findFirst(int x, int l, int r, int ql, int qr, F pred) {
        if (l > qr || r < ql || !pred(info[x]))
            return -1;
        if (l == r)
            return l;
        int mid = l + r >> 1;
        pushdown(x);
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
        int mid = l + r >> 1;
        pushdown(x);
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
struct Tag {
    ll add = 0;
    void apply(const Tag& v) { add += v.add; }  // 标记怎么合并
};
struct Info {
    ll sum = 0, len = 1;
    void apply(const Tag& v) { sum += len * v.add; }  // 标记怎么更新节点信息
};
Info operator+(const Info& a, const Info& b) {  // 维护的信息怎么合并
    Info c = Info();
    c.sum = a.sum + b.sum;
    c.len = a.len + b.len;
    return c;
}