#include <array>
#include <string>
#include <vector>

// 毛坯房
class trie {
    const int size = 1e5 + 10;
    int idx;
    std::vector<std::array<int, 26>> tr;  // 字母数量喵
    std::vector<int> cnt;

    int newnode() {
        tr[idx].fill(0);
        cnt[idx] = 0;
        idx++;
        return idx - 1;
    }

public:
    trie() : idx(1), tr(size), cnt(size) {}
    void insert(const std::string &s) {
        int p = 0;
        for (auto i : s) {
            i -= 'a';  // 要映射到0开始的喵
            if (!tr[p][i]) {
                tr[p][i] = newnode();
            }
            p = tr[p][i];
        }
        cnt[p]++;
    }
    void clean() {
        idx = 0;
        newnode();
    }
} tr;
