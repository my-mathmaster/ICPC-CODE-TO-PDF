template <class Info>
struct Segment {
    struct Node {
        int left, right;
        Info info;
        Node() : left{0}, right{0}, info{} {}
    };
    int n;
    vector<Node> t;
    Segment(int n = 0) { init(n); }
    void init(int n) {
        this->n = n;
        t.assign(1, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int modify(int prev, int l, int r, int x, const Info &v) {
        int curr = newNode();
        t[curr] = t[prev];
        t[curr].info.apply(v);
        if (r - l == 1) {
            return curr;
        }
        int m = (l + r) / 2;
        if (x < m) {
            t[curr].left = modify(t[prev].left, l, m, x, v);
        } else {
            t[curr].right = modify(t[prev].right, m, r, x, v);
        }
        return curr;
    }
    int modify(int prev, int x, const Info &v) { return modify(prev, 0, n, x, v); }
    Info query(int L, int R, int l, int r, int x) {
        if (r - l == 1) {
            return t[R].info - t[L].info;
        }
        int m = (l + r) / 2;
        if (x < m) {
            return query(t[L].left, t[R].left, l, m, x);
        } else {
            return query(t[L].right, t[R].right, m, r, x);
        }
    }
    Info query(int L, int R, int x) { return query(L, R, 0, n, x); }
    Info rangeQuery(int L, int R, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return t[R].info - t[L].info;
        }
        int m = (l + r) / 2;
        return rangeQuery(t[L].left, t[R].left, l, m, x, y) + rangeQuery(t[L].right, t[R].right, m, r, x, y);
    }
    Info rangeQuery(int L, int R, int l, int r) { return rangeQuery(L, R, 0, n, l, r); }
};

struct Info {
    int x;
    Info(int x = 0) : x{x} {}
    void apply(const Info &v) { x += v.x; }
};
Info operator+(Info lhs, Info rhs) {
    Info res = lhs;
    res.x += rhs.x;
    return res;
}
Info operator-(Info lhs, Info rhs) {
    Info res = lhs;
    res.x -= rhs.x;
    return res;
}