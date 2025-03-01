#include <string>
#include <vector>

/// 获取最大真公共前后缀, 传入的s 0-index
std::vector<int> get_next(const std::string &s) {
    int len = s.size();
    std::vector<int> nex(len);
    for (int i = 1; i < len; i++) {
        int p = nex[i - 1];
        while (p && s[p] != s[i]) p = nex[p - 1];  // 后一个和当前的不匹配
        if (s[p] == s[i])
            p++;  // 后一个和当前匹配
        nex[i] = p;
    }
    return nex;
}

/// nex = get_next(b)
std::vector<int> kmp(const std::string &a, const std::string &b, const std::vector<int> &nex) {
    int len1 = a.size(), len2 = b.size();
    std::vector<int> res(len1);
    int p = 0;
    for (int i = 0; i < len1; i++) {
        while (p == len2 || (p && a[i] != b[p])) p = nex[p - 1];
        if (a[i] == b[p])
            p++;
        res[i] = p;
    }
    return res;
}