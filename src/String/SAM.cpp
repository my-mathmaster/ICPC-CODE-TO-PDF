struct SAM {
    static constexpr int asz = 26;
    struct Node {
        int len;
        int fail;
        int cnt = 0;
        array<int, asz> next;
        Node() : len{}, fail{}, next{} {}
    };
    vector<Node> t;
    int tot = 0;
    SAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int nq = newNode();
            t[nq].len = t[p].len + 1;
            t[nq].fail = t[q].fail;
            t[nq].next = t[q].next;
            t[q].fail = nq;
            while (t[p].next[c] == q) {
                t[p].next[c] = nq;
                p = t[p].fail;
            }
            return nq;
        }
        int np = newNode();
        t[np].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = np;
            p = t[p].fail;
        }
        t[np].fail = extend(p, c);
        t[np].cnt += 1;
        return np;
    }
    int extend(int p, char c, char offset = 'a') {
        return extend(p, c - offset);
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }

    int fail(int p) {
        return t[p].fail;
    }

    int len(int p) {
        return t[p].len;
    }
    int size() {
        return t.size();
    }
    int &cnt(int p) {
        return t[p].cnt;
    }
    void work(string s) {
        int p = 1;
        // vector<int> pos(1, 0);
        for (auto x : s) {
            p = extend(p, x);
            // pos.push_back(p);
        }
        tot = t.size() - 1;
        // return pos;
    }
    void getcnt(int len) {
        vector<int> tong(len + 1);
        vector<int> id(tot + 1);
        for (int i = 1; i <= tot; i++) tong[t[i].len]++;
        // 按照len[x]从小到大基数排序，相当于对SAM图进行拓扑排序
        for (int i = 1; i <= n; i++) tong[i] += tong[i - 1];
        for (int i = 1; i <= tot; i++) id[tong[t[i].len]--] = i;  // 排名为j的节点是状态i
        for (int i = tot; i >= 1; i--) {
            auto cur = t[id[i]];
            t[cur.fail].cnt += cur.cnt;
        }
        // 从后往前for,自底向上更新parent的right大小
    }
};