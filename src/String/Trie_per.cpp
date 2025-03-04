struct Trie_per {
    static constexpr int SIZE = 2;
    static constexpr int width = 24;  // 值域小于2的width次方
    struct Node {
        int cnt;
        array<int, SIZE> next;
        Node() : cnt{0}, next{} {}
    };
    vector<Node> t;
    vector<int> ver;
    Trie_per() { init(); }
    void init() {
        t.assign(2, {});
        ver.resize(1);
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int add(int pre, const vector<int> &a) {
        int cur = newNode();
        int p = pre, q = cur;
        t[q] = t[p];
        for (auto x : a) {
            t[q].next[x] = newNode();
            p = next(p, x);
            q = next(q, x);
            t[q] = t[p];
            t[q].cnt++;
        }
        return cur;
    }
    int add(int pre, int x) {  // 转成01vector
        vector<int> a;
        for (int i = width - 1; i >= 0; i--) {
            a.push_back((x >> i) & 1);
        }
        return add(pre, a);
    }
    void add(int x) {  // 外部接口，加入一个数生成一个新版本
        int pos = add(ver.back(), x);
        ver.push_back(pos);
    }
    // 查询x在版本(l,r]中和哪个数异或最大
    int querymx(int l, int r, int x) {  // 传l-1进来
        int res = 0;
        int p = ver[l], q = ver[r];
        for (int i = width - 1; i >= 0; i--) {
            int u = (x >> i) & 1;
            int nxp = t[p].next[u ^ 1], nxq = t[q].next[u ^ 1];
            if (t[nxq].cnt - t[nxp].cnt > 0) {
                res |= 1 << i;
                u ^= 1;
            }
            p = t[p].next[u];
            q = t[q].next[u];
        }
        return res;
    }
    int size() { return t.size(); }
    int cnt(int p) { return t[p].cnt; }
    int next(int p, int x) { return t[p].next[x]; }
};