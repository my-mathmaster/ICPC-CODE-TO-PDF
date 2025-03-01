#include <random>
#include <string>
#include <vector>

class Hash {
    static int findprime() {
        std::random_device rd;
        std::mt19937 gen(rd());
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
    const int B1 = 131;
    const int B2 = 13331;
    std::vector<int> f1, pow1;

public:
    using LL = long long;

    Hash() : f1(1), pow1(1, 1) {}
    Hash(const std::string &s) : f1(1), pow1(1, 1) {
        insert(s);
    }

    // 0-base
    int get(int l, int r) const {
        l++, r++;
        return (f1[r] - (LL)f1[l - 1] * pow1[r - l + 1] % Mod + Mod) % Mod;
    }
    void insert(const std::string &s) {
        int len1 = f1.size(), len2 = s.size();
        f1.resize(len1 + len2);
        pow1.resize(std::max<int>(len1 + len2, pow1.size()));
        for (int i = len1; i < len1 + len2; i++) {
            pow1[i] = (LL)pow1[i - 1] * B1 % Mod;
            f1[i] = ((LL)f1[i - 1] * B1 + s[i - len1]) % Mod;
        }
    }
    void clear() {
        f1.resize(1);
    }
};

const int Hash::Mod = Hash::findprime();

class Hash2 {
    static int findprime() {
        std::random_device rd;
        std::mt19937 gen(rd());
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
    const int B1 = 131;
    const int B2 = 13331;
    std::vector<int> f1, f2, pow1, pow2;

public:
    using LL = long long;

    Hash2() : f1(1), f2(1), pow1(1, 1), pow2(1, 1) {}
    Hash2(const std::string &s) : f1(1), f2(1), pow1(1, 1), pow2(1, 1) {
        insert(s);
    }

    // 0-base
    std::pair<int, int> get(int l, int r) {
        l++, r++;
        return {(f1[r] - (LL)f1[l - 1] * pow1[r - l + 1] % Mod + Mod) % Mod,
                (f2[r] - (LL)f2[l - 1] * pow2[r - l + 1] % Mod + Mod) % Mod};
    }
    void insert(const std::string &s) {
        int len1 = f1.size(), len2 = s.size();
        f1.resize(len1 + len2), f2.resize(len1 + len2);
        pow1.resize(std::max<int>(len1 + len2, pow1.size())), pow2.resize(std::max<int>(len1 + len2, pow1.size()));
        for (int i = len1; i < len1 + len2; i++) {
            pow1[i] = (LL)pow1[i - 1] * B1 % Mod;
            f1[i] = ((LL)f1[i - 1] * B1 + s[i - len1]) % Mod;
            pow2[i] = (LL)pow2[i - 1] * B2 % Mod;
            f2[i] = ((LL)f2[i - 1] * B2 + s[i - len1]) % Mod;
        }
    }
    void clear() {
        f1.resize(1), f2.resize(1);
    }
};

const int Hash2::Mod = Hash2::findprime();