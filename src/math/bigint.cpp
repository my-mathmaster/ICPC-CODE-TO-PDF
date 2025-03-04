using uint = unsigned;
const int MOD = 998244353; // NTT模数

// 模加法
int Add(int x, int y) { return (x + y >= MOD) ? x + y - MOD : x + y; }
// 模减法
int Dec(int x, int y) { return (x - y < 0) ? x - y + MOD : x - y; }
// 模乘法
int mul(int x, int y) { return 1ll * x * y % MOD; }
// 快速幂计算
uint qp(uint a, int b) { 
    uint res = 1; 
    for (; b; b >>= 1, a = mul(a, a))  
        if (b & 1)  
            res = mul(res, a); 
    return res; 
}

namespace NTT {
    int sz; // FFT大小
    uint w[2500005], w_mf[2500005]; // 存储预计算的单位根及其乘法因子
    // 计算乘法因子
    int mf(int x) { return (1ll * x << 32) / MOD; }
    // 初始化NTT
    void init(int n) {
        for (sz = 2; sz < n; sz <<= 1);
        uint pr = qp(3, (MOD - 1) / sz);
        w[sz / 2] = 1; 
        w_mf[sz / 2] = mf(1);
        for (int i = 1; i < sz / 2; i++) {
            w[sz / 2 + i] = mul(w[sz / 2 + i - 1], pr);
            w_mf[sz / 2 + i] = mf(w[sz / 2 + i]);
        }
        for (int i = sz / 2 - 1; i; i--) {
            w[i] = w[i << 1];
            w_mf[i] = w_mf[i << 1];
        }
    }
    // 前向NTT
    void ntt(vector<uint>& A, int L) {
        for (int d = L >> 1; d; d >>= 1) {
            for (int i = 0; i < L; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    uint x = A[i + j] + A[i + d + j];
                    if (x >= 2 * MOD) x -= 2 * MOD;
                    ll t = A[i + j] + 2 * MOD - A[i + d + j];
                    ll q = t * w_mf[d + j] >> 32; 
                    int y = t * w[d + j] - q * MOD;
                    A[i + j] = x; 
                    A[i + d + j] = y;
                }
            }
        }
        for (int i = 0; i < L; i++) {
            if (A[i] >= MOD) A[i] -= MOD;
        }
    }
    // 逆NTT
    void intt(vector<uint>& A, int L) {
        for (int d = 1; d < L; d <<= 1) {
            for (int i = 0; i < L; i += (d << 1)) {
                for (int j = 0; j < d; j++) {
                    uint x = A[i + j]; 
                    if (x >= 2 * MOD) x -= 2 * MOD;
                    ll t = A[i + d + j];
                    ll q = t * w_mf[d + j] >> 32;
                    int y = t * w[d + j] - q * MOD;
                    A[i + j] = x + y; 
                    A[i + d + j] = x + 2 * MOD - y;
                }
            }
        }
        int k = (L & (-L));
        reverse(A.begin() + 1, A.end());
        for (int i = 0; i < L; i++) {
            ll m = -A[i] & (L - 1);
            A[i] = (A[i] + m * MOD) / k;
            if (A[i] >= MOD) A[i] -= MOD;
        }
    }
}

struct bigint {
    vector<int> nums; // 存储大整数的每一位
    int operator[](const int& k)const { return nums[k]; }
    int& operator[](const int& k) { return nums[k]; }
    int size() { return nums.size(); }
    void push_back(int x) { nums.push_back(x); }
    // 从整数构造大整数
    bigint(int x = 0) {
        do {
            nums.push_back(x % 10);
            x /= 10;
        } while (x);
    }
    // 从字符串构造大整数
    bigint(string s) {
        for (int i = s.size() - 1; i >= 0; i--)
            nums.push_back(s[i] - '0');
        trim();
    }
    // 去掉多余的前导零
    void trim() {
        while (nums.size() > 1 && nums.back() == 0) {
            nums.pop_back();
        }
    }
    // 清空大整数
    void clear() {
        nums.clear();
    }
    // 输入大整数
    friend istream& operator>>(istream& cin, bigint& num) {
        string tnum;
        cin >> tnum;
        num = tnum;
        return cin;
    }
    // 输出大整数
    friend ostream& operator<<(ostream& cout, bigint num) {
        bool start = false;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (!start && num[i] == 0)
                continue;
            start = true;
            cout << num[i];
        }
        if (!start)
            cout << 0;
        return cout;
    }
};

// 比较运算符重载
bool operator<(bigint a, bigint b) {
    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}

bool operator>(bigint a, bigint b) {
    return b < a;
}

bool operator<=(bigint a, bigint b) {
    return !(a > b);
}

bool operator>=(bigint a, bigint b) {
    return !(a < b);
}

bool operator==(bigint a, bigint b) {
    return !(a < b) && !(a > b);
}

bool operator!=(bigint a, bigint b) {
    return a < b || a > b;
}

// 大整数加法
bigint operator+(bigint a, bigint b) {
    bigint res;
    res.clear();
    int t = 0;
    int mx = max(a.size(), b.size());
    for (int i = 0; i < mx || t; i++) {
        if (i < a.size()) {
            t += a[i];
        }
        if (i < b.size()) {
            t += b[i];
        }
        res.push_back(t % 10);
        t /= 10;
    }
    res.trim();
    return res;
}

// 大整数减法
bigint operator-(bigint a, bigint b) {
    bigint res(a);
    bigint sub(b);
    int flag = 0;
    int len = res.size();
    while (sub.size() < res.size())
        sub.push_back(0);
    for (int i = 0; i < len; i++) {
        if (res[i] + flag >= sub[i]) {
            res[i] = res[i] + flag - sub[i];
            flag = 0;
        }
        else {
            res[i] = res[i] + 10 + flag - sub[i];
            flag = -1;
        }
    }
    res.trim();
    return res;
}

// 大整数乘法（nlogn）
bigint operator*(bigint a, bigint b) {
    bigint res;
    res.nums.pop_back();
    int dega = a.size() - 1, degb = b.size() - 1;
    int n = dega + degb + 1;
    int lim;
    for (lim = 1; lim < n; lim <<= 1); 
    NTT::init(lim);
    vector<uint> A(lim);
    for (int i = 0; i <= dega; i++) A[i] = a[i];
    vector<uint> B(lim);
    for (int i = 0; i <= degb; i++) B[i] = b[i];
    NTT::ntt(A, lim);
    NTT::ntt(B, lim);
    for (int i = 0; i < lim; i++) A[i] = mul(A[i], B[i]);
    NTT::intt(A, lim);
    for (int i = 0, t = 0; i < lim || t; i++) {
        if (i < lim) t += A[i];
        res.push_back(t % 10);
        t /= 10;
    }
    res.trim();
    return res;
}

// 大整数与长整数乘法
bigint operator*(bigint a, ll b) {
    bigint res(a);
    int carry = 0;
    for (int i = 0; i < a.size(); i++) {
        carry += a[i] * b;
        res[i] = carry % 10;
        carry /= 10;
    }
    while (carry > 0) {
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

// 大整数除法
bigint operator/(bigint a, bigint b) {
    bigint tnum(a);
    if (a < b)
        return 0;
    int n = a.size() - b.size();
    b.nums.insert(b.nums.begin(), n, 0);
    if (tnum >= b) {
        n++;
        b.nums.insert(b.nums.begin(), 0);
    }
    bigint ans;
    ans.nums.assign(n, 0);
    int n2 = b.size();
    while (n--) {
        n2--;
        b.nums.erase(b.nums.begin());
        while (!(tnum < b)) {
            int n1 = tnum.size();
            for (int j = 0; j < n2; j++) {
                tnum[j] -= b[j];
                if (tnum[j] < 0) {
                    tnum[j + 1]--;
                    tnum[j] += 10;
                }
            }
            tnum.trim();
            ans[n]++;
        }
    }
    ans.trim();
    return ans;
}

// 大整数与长整数除法
bigint operator/(bigint a, ll b) {
    bigint ans;
    ans.clear();
    int r = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        r = r % b * 10 + a[i];
        ans.push_back(r / b);
    }
    reverse(ans.nums.begin(), ans.nums.end());
    ans.trim();
    return ans;
}

// 大整数取模
bigint operator%(bigint a, bigint b) {
    bigint div_res = a / b;
    return a - div_res * b;
}

// 大整数与长整数取模
bigint operator%(bigint a, ll b) {
    bigint div_res = a / b;
    return a - div_res * b;
}

// 大整数快速幂
bigint qp(bigint a, ll n) {
    bigint res(1);
    while (n) {
        if (n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

// 大整数组合数
bigint comb(bigint n, bigint m) {
    bigint res = 1;
    for (bigint up = n, down = 1; down <= m; up = up - 1, down = down + 1)
        res = res * up, res = res / down;
    return res;
}
