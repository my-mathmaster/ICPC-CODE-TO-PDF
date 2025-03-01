#include <string>
#include <vector>

/// @brief manacher's algorithm
/// @param s the string to be processed
/// @return use l+r to be index (1-index)
std::vector<int> manacher(const std::string &s) {
    using namespace std::literals;
    std::string ss;
    for (auto &i : s) {
        ss += "#"s + i;
    }
    ss = '!' + ss + "#?";

    std::vector<int> p(ss.size());
    int c = 1, r = 1;
    for (int i = 1; i < ss.size(); i++) {
        p[i] = std::min(p[2 * c - i], r - i);
        while (ss[i + 1 + p[i]] == ss[i - 1 - p[i]])
            p[i]++;
        if (p[i] + i > r)
            r = p[i] + i, c = i;
    }
    return p;
}