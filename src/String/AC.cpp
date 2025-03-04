struct AC {                         // 定义了AhoCorasick结构体，用于实现Aho-Corasick字符串匹配算法
    static constexpr int asz = 26;  // 定义常量ALPHABET为26，表示字母表的大小（26个小写字母）
    struct Node {                   // 定义了内部结构体Node，表示Trie树的一个节点
        int len;                    // 节点对应的字符串的长度
        int fail;                   // 节点的后缀链接，指向最长的可以匹配的后缀节点
        array<int, asz> next;
        // 表示从当前节点到下一个节点的转换，数组大小为字母表大小
        Node() : len{0}, fail{0}, next{} {}  // 构造函数，初始化len为0，link为0，next数组全为0
    };

    vector<Node> t;  // 定义一个Node类型的向量，存储Trie树中的所有节点

    AC() {  // 构造函数，调用init函数初始化Trie树
        init();
    }

    void init() {             // 初始化Trie树，创建根节点和伪根节点
        t.assign(2, Node());  // 创建两个节点，分别是根节点和伪根节点
        t[0].next.fill(1);    // 将根节点的所有next指向伪根节点
        t[0].len = -1;        // 设置根节点的len为-1
    }

    int newNode() {           // 创建一个新节点，并返回其索引
        t.emplace_back();     // 向向量t中添加一个新的Node节点
        return t.size() - 1;  // 返回新节点的索引
    }

    int add(const string &a) {                       // 向Trie树中添加字符串，并返回最后一个字符对应的节点索引
        int p = 1;                                   // 从伪根节点开始
        for (auto c : a) {                           // 遍历字符串中的每个字符
            int x = c - 'a';                         // 计算字符在字母表中的索引
            if (t[p].next[x] == 0) {                 // 如果当前字符的路径不存在
                t[p].next[x] = newNode();            // 创建新节点，并更新next数组
                t[t[p].next[x]].len = t[p].len + 1;  // 设置新节点的len为当前节点len加1
            }
            p = t[p].next[x];  // 移动到下一个节点
        }
        return p;  // 返回最后一个字符对应的节点索引
    }

    void work() {      // 构建Aho-Corasick自动机的后缀链接
        queue<int> q;  // 创建队列，用于广度优先搜索
        q.push(1);     // 将伪根节点加入队列

        while (!q.empty()) {    // 当队列不为空时，进行循环
            int x = q.front();  // 取出队列头部的节点
            q.pop();            // 移除队列头部的节点

            for (int i = 0; i < asz; i++) {                       // 遍历所有可能的字符
                if (t[x].next[i] == 0) {                          // 如果当前节点没有对应字符的转移
                    t[x].next[i] = t[t[x].fail].next[i];          // 设置为后缀链接节点的对应转移
                } else {                                          // 如果有对应字符的转移
                    t[t[x].next[i]].fail = t[t[x].fail].next[i];  // 设置新节点的后缀链接
                    q.push(t[x].next[i]);                         // 将新节点加入队列
                }
            }
        }
    }

    int next(int p, int x) {  // 获取节点p的字符x的转移
        return t[p].next[x];
    }

    int fail(int p) {  // 获取节点p的后缀链接
        return t[p].fail;
    }

    int len(int p) {  // 获取节点p对应的字符串长度
        return t[p].len;
    }

    int size() {  // 获取Trie树的节点总数
        return t.size();
    }
};

void solve() {
    AC ac;
    cin >> n;
    vector<int> id(n + 1);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        id[i] = ac.add(s);
    }

    ac.work();
    string tt;
    int p = 1;
    cin >> tt;
    int tot = ac.size();
    vector<int> sz(tot);

    m = tt.size();
    for (int i = 0; i < m; i++) {
        int ch = tt[i] - 'a';
        p = ac.next(p, ch);
        sz[p] += 1;
        deb(p);
    }
    vector<vector<int>> e(tot);
    for (int i = 2; i < tot; i++) {
        deb(i, ac.fail(i));
        e[ac.fail(i)].push_back(i);
    }
    auto dfs = [&](auto self, int u) -> void {
        for (auto v : e[u]) {
            self(self, v);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 1);
    for (int i = 1; i <= n; i++) cout << sz[id[i]] << endl;
}