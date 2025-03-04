template <class info, class tag>
class LSGT {
    std::vector<info> node;
    std::vector<tag> ta;
    int siz;
    void build(int idx, int l, int r) {
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(idx << 1, l, mid), build(idx << 1 | 1, mid + 1, r);
        node[idx] = node[idx << 1] + node[idx << 1 | 1];
    }
    template <typename T>
    void build(int idx, int l, int r, const std::vector<T> &vec) {
        if (l == r) {
            node[idx] = vec[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(idx << 1, l, mid, vec), build(idx << 1 | 1, mid + 1, r, vec);
        node[idx] = node[idx << 1] + node[idx << 1 | 1];
    }
    void apply(int idx) {
        if (ta[idx].empty())
            return;
        ta[idx << 1].apply(ta[idx]);
        ta[idx << 1 | 1].apply(ta[idx]);
        node[idx << 1].apply(ta[idx]);
        node[idx << 1 | 1].apply(ta[idx]);
        ta[idx] = {};
    }
    void modify(int idx, int l, int r, int ql, int qr, const tag &add) {
        if (ql <= l && qr >= r) {
            ta[idx].apply(add);
            node[idx].apply(add);
            return;
        }
        apply(idx);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            modify(idx << 1, l, mid, ql, qr, add);
        if (qr > mid)
            modify(idx << 1 | 1, mid + 1, r, ql, qr, add);
        node[idx] = node[idx << 1] + node[idx << 1 | 1];
    }
    info query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && qr >= r)
            return node[idx];
        apply(idx);
        int mid = (l + r) >> 1;
        if (qr <= mid)
            return query(idx << 1, l, mid, ql, qr);
        else if (ql > mid)
            return query(idx << 1 | 1, mid + 1, r, ql, qr);
        else
            return query(idx << 1, l, mid, ql, qr) + query(idx << 1 | 1, mid + 1, r, ql, qr);
    }

public:
    LSGT(const int size) : node(size << 2), ta(size << 2), siz(size) {
        build(1, 1, siz);
    }
    template <typename T>
    LSGT(const std::vector<T> &vec) : node(vec.size() << 2), ta(vec.size() << 2), siz(vec.size() - 1) {
        build(1, 1, siz, vec);
    }
    void modify(int ql, int qr, const tag &add) {
        modify(1, 1, siz, ql, qr, add);
    }
    info query(int ql, int qr) {
        return query(1, 1, siz, ql, qr);
    }
};
//区间加/区间和
struct tag {
    long long add;
    tag() : add(0) {}
    tag(long long x) : add(x) {}
    bool empty() const {
        return !add;
    }
    void apply(const tag &o) {
        add += o.add;
    }
};
struct info {
    int len;
    long long sum;
    info() : len(1), sum(0) {}
    info(long long x) : len(1), sum(x) {}
    info(int len, long long sum) : len(len), sum(sum) {}
    info operator+(const info &o) const {
        return info{len + o.len, sum + o.sum};
    }
    void apply(const tag &o) {
        sum += o.add * len;
    }
};

//区间最小值计数
struct tag {
    int add;
    tag() : add(0) {}
    tag(int x) : add(x) {}
    bool empty() const {
        return !add;
    }
    void apply(const tag &o) {
        add += o.add;
    }
};
struct info {
    int minn;
    long long sum;
    info() : minn(0), sum(0) {}
    info(long long sum) : minn(0), sum(sum) {}
    info(int minn, long long sum) : minn(minn), sum(sum) {}
    info operator+(const info &o) const {
        if (minn == o.minn) {
            return {minn, sum + o.sum};
        } else {
            return minn < o.minn ? *this : o;
        }
    }
    void apply(const tag &o) {
        minn += o.add;
    }
};