struct PAM {
    static constexpr int asz = 28;
    struct Node {
        int len;
        int fail;
        int dep;      // 以这个节点结尾的回文子串的数量(回文fail树的深度)
        int cnt = 0;  // 同样的回文结构出现次数
        array<int, asz> next;
        // int mask = 0;用了多少种字母
        Node() : len{}, fail{}, dep{}, next{} {}
    };
    vector<Node> t;
    vector<int> idpos;  // idpos表示字符串字符位置到后缀自动机节点编号
    int last;
    string s;
    PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;  // 0：奇根
        last = 1;       // 1：偶根
        s.clear();
        idpos.assign(1, 0);
    }
    int newNode() {
        t.emplace_back();  // Node()
        return t.size() - 1;
    }

    bool add(char c, char offset = 'a') {
        int pos = s.size();
        s += c;
        int ch = c - offset;
        int cur = last, curlen = 0;

        while (true) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = t[cur].fail;
        }  // 找到在哪个节点后面建新点
        if (t[cur].next[ch]) {
            last = t[cur].next[ch];
            idpos.push_back(last);
            t[last].cnt += 1;
            return false;
        }

        int num = newNode();
        last = num;
        idpos.push_back(last);
        t[num].len = t[cur].len + 2;
        // 在这里加入题目需要维护的值
        // t[num].mask = t[cur].mask;
        // t[num].mask |= 1 << ch;
        t[cur].next[ch] = num;

        if (t[num].len == 1) {  // 如果为单字符，指向偶根
            t[num].fail = 1;
            t[num].dep = 1;
            t[num].cnt = 1;
            return true;
        }

        while (true) {  // 为新节点找fail，从父亲的fail开始找
            cur = t[cur].fail;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[num].fail = t[cur].next[ch];
                break;
            }
        }
        t[num].cnt = 1;
        t[num].dep = 1 + t[t[num].fail].dep;

        return true;
    }
    int tot = 0;
    void work(string tt) {
        for (auto x : tt) add(x);
        tot = t.size() - 1;
        for (int i = tot; i >= 0; i--) {
            int fa = t[i].fail;
            t[fa].cnt += t[i].cnt;
        }
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
    int cnt(int p) {
        return t[p].cnt;
    }
};