istream &operator>>(istream &is, __int128 &T) {
    char c;
    int f = 1;
    T = 0;
    c = is.get();
    while (c != '-' && !isdigit(c)) c = is.get();
    if (c == '-')
        f = -1, c = is.get();
    while (isdigit(c)) {
        T = T * 10 + (c - '0');
        c = is.get();
    }
    T = f * T;
    return is;
}
std::ostream &operator<<(std::ostream &os, __int128 &n) {
    std::string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}