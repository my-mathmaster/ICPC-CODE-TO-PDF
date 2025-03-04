struct Hash {
    static int findprime() {
        random_device rd;
        mt19937 gen(rd());

        int n = gen() % 900000000 + 100000000;
        if (n % 2 == 0)
            n++;
        while (true) {
            bool ok = 1;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    ok = 0;
                    n += 2;
                    break;
                }
            }
            if (ok)
                return n;
        }
    }

    static const int Mod;
    static vector<int> pow1;
    static vector<int> pow2;
    const int B1 = 131;
    const int B2 = 13331;
    string s;
    int len = 0;
    vector<int> f1, f2;
    using LL = long long;

    Hash() {}
    Hash(const string &t, bool rfg = 0) {
        init(t, rfg);
    }
    // 默认前缀哈希
    void init(const string &t, bool rfg = 0) {
        s = " " + t;
        len = t.size();
        int cur = pow1.size();
        if (cur - 1 <= len) {
            pow1.resize(len + 1, 1);
            pow2.resize(len + 1, 1);
            for (int i = cur; i <= len; i++) {
                pow1[i] = (LL)pow1[i - 1] * B1 % Mod;
                pow2[i] = (LL)pow2[i - 1] * B2 % Mod;
            }
        }
        f1.resize(len + 2, 0);
        f2.resize(len + 2, 0);
        if (rfg == 0)
            insert1(s);
        else
            insert2(s);
    }

    // 1-base
    pair<int, int> getpre(int l, int r) const {
        int res1 = (f1[r] - (LL)f1[l - 1] * pow1[r - l + 1] % Mod + Mod) % Mod;
        int res2 = (f2[r] - (LL)f2[l - 1] * pow2[r - l + 1] % Mod + Mod) % Mod;
        return make_pair(res1, res2);
    }
    pair<int, int> getsuf(int l, int r) const {
        int res1 = (f1[l] - (LL)f1[r + 1] * pow1[r - l + 1] % Mod + Mod) % Mod;
        int res2 = (f2[l] - (LL)f2[r + 1] * pow2[r - l + 1] % Mod + Mod) % Mod;
        return make_pair(res1, res2);
    }
    // 前缀哈希
    void insert1(const string &t) {
        for (int i = 1; i <= len; i++) {
            f1[i] = ((LL)f1[i - 1] * B1 + t[i]) % Mod;
            f2[i] = ((LL)f2[i - 1] * B2 + t[i]) % Mod;
        }
    }
    // 后缀哈希
    void insert2(const string &t) {
        for (int i = len; i >= 1; i--) {
            f1[i] = ((LL)f1[i + 1] * B1 + t[i]) % Mod;
            f2[i] = ((LL)f2[i + 1] * B2 + t[i]) % Mod;
        }
    }

    void clear() {
        f1.resize(1);
        f2.resize(1);
    }
};
const int Hash::Mod = Hash::findprime();
vector<int> Hash::pow1(1, 1);
vector<int> Hash::pow2(1, 1);