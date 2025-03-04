int id(char c) {  // 给出现的字符集编码，记得改offset部分
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 26;
    else
        return c - '0' + 52;
}
struct Trie {  // 正常字母字符串trie
    static constexpr int ALPHA = 26;
    struct Node {
        int cnt;
        bool ended;
        array<int, ALPHA> next;
        Node() : cnt{0}, ended{false}, next{} {}
    };
    vector<Node> t;
    Trie() { init(); }
    void init() {
        t.assign(2, {});
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int add(const vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
            t[p].cnt++;
        }
        t[p].ended = true;
        return p;
    }
    int add(const string &s, char offset = 'a') {
        vector<int> a;
        for (auto c : s) {
            a.push_back(c - offset);
        }
        return add(a);
    }
    int cnt(int p) { return t[p].cnt; }
    bool ended(int p) { return t[p].ended; }
    int next(int p, int x) { return t[p].next[x]; }
    int next(int p, char c, char offset = 'a') { return next(p, c - offset); }
    int size() { return t.size(); }
};
Trie tr;