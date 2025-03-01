#include <string>
#include <vector>

/// 获取最大公共后缀, 传入的s 0-index
std::vector<int> get_z(const std::string &s) {
    int len = s.size();
    std::vector<int> z(len);
    z[0] = len;
    int L = 0, R = -1;
    for (int i = 1; i < len; i++) {
        int k = i - L;
        if (i <= R)
            z[i] = std::min(z[k], R - i + 1);
        else
            z[i] = 0;
        while (i + z[i] < len && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > R)
            L = i, R = i + z[i] - 1;
    }
    return z;
}

/// z = get_z(b)
std::vector<int> exkmp(const std::string &a, const std::string &b, const std::vector<int> &z) {
    int len1 = a.size(), len2 = b.size();
    std::vector<int> res(len1);
    int L = 0, R = -1;
    for (int i = 0; i < len1; i++) {
        int k = i - L;
        if (i <= R)
            res[i] = std::min(z[k], R - i + 1);
        else
            res[i] = 0;
        while (res[i] < len2 && i + res[i] < len1 && a[i + res[i]] == b[res[i]]) res[i]++;
        if (i + res[i] > R)
            L = i, R = i + res[i] - 1;
    }
    return res;
}