mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
mt19937_64 rnd_64(chrono::system_clock::now().time_since_epoch().count());
int rndi(int r) { return rnd() % r; }                        // 随机生成0-(r-1)
int rndi(int l, int r) { return rnd() % (r - l + 1) + l; }   // 随机生成l-r
LL rndll(LL l, LL r) { return rnd_64() % (r - l + 1) + l; }  // 随机生成0-(r-1)
char rndc() { return rndi(-128, 127); }                      // 生成 ASCII 码在 [-128, 127] 范围内的随机字符
char rndc(const string &s) { return s[rndi(s.length())]; }   // 从给定字符串 s 中随机选择一个字符
char rnd_lower() { return rndi(26) + 'a'; }                  // 随机小写字母
char rnd_upper() { return rndi(26) + 'A'; }                  // 大写
char rnd_digit() { return rndi(10) + '0'; }                  // 数字
char rnd_alpha() { // 大小写
    int r = rndi(52);
    return r < 26 ? (r + 'a') : (r - 26 + 'A');
}                        
char rnd_alphadigit() {  // 大小写+数字
    int r = rndi(62);
    if (r < 10)
        return r + '0';
    if (r < 36)
        return r - 10 + 'a';
    return r - 36 + 'A';
}
template <typename T>  // n 个随机值的 vector
vector<T> rnd_vec(int n, const function<T(void)> &f) {
    vector<T> vec;
    while (n--) vec.push_back(f());
    return vec;
}
// n个[l, r] 范围内的随机int
vector<int> rnd_vii(int n, int l, int r) {
    return rnd_vec<int>(n, [=]() { return rndi(l, r); });
}
// n 个在 [l, r] 范围内的随机 long long
vector<LL> rnd_vll(int n, LL l, LL r) {
    return rnd_vec<LL>(n, [=]() { return rndll(l, r); });
}
// 一个长度为 n 的随机字符串。每个字符由函数 f 生成。
string rnds(int n, const function<char(void)> &f) {
    string s;
    while (n--) s += f();
    return s;
}
// cout << rnds(10, []() { return rndc("abc"); }) << endl;
// 生成并输出一个由 10 个从字符串 "abc" 中随机选择的字符组成的字符串。