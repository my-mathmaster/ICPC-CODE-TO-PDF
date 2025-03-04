struct Trie_bin {  // 保证第一次一定是先插入，查询不能先做
    static constexpr int ALPHA = 2;
    static constexpr int width = 21;  // 值域必须小于2的width次方
    struct Node {
        int cnt = 0;
        array<int, ALPHA> next;
        Node() : next{} {}
    };
    vector<Node> t;
    Trie_bin() { init(); }
    void init() {
        t.assign(2, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    // 增加flag标志便于删除
    int add(const vector<int> &a, int flag) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
            t[p].cnt += flag;
        }
        return p;
    }
    // 数字转01串vector
    int add(int x, int flag = 1) {  // x必须小于2的width次方
        vector<int> a;
        for (int i = width - 1; i >= 0; i--) {
            a.push_back((x >> i) & 1);
        }
        return add(a, flag);
    }
    int querymx(int x) {
        int res = 0, p = 1;
        for (int i = width - 1; i >= 0; i--) {
            int u = (x >> i) & 1;
            int nxp = t[p].next[u ^ 1];
            if (nxp && t[nxp].cnt) {
                res |= 1 << i;
                u ^= 1;
            }
            p = t[p].next[u];
        }
        return res;
    }
    int next(int p, int x) { return t[p].next[x]; }
    int size() { return t.size(); }
    int cnt(int p) {
        return t[p].cnt;
    }
};
Trie_bin tr;