#include <string>

std::string mini(std::string s) {
    int len = s.size();
    s += s;
    int i = 0, j = 1;

    while (j < len) {
        int k = 0;
        while (k < len && s[i + k] == s[j + k]) k++;
        if (s[i + k] > s[j + k])
            i += k + 1;
        else
            j += k + 1;
        if (i == j)
            j++;
        else if (i > j)
            std::swap(i, j);
    }

    return s.substr(i, len);
}