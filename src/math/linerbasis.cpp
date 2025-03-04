int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
struct linerbasis {
    static const int mxl = 30;
    int a[mxl + 1];
    int n = 0;        // 尝试插入次数
    int tot = 0;      // 线性基大小
    vector<int> tmp;  // 有效位集中

    linerbasis() {
        std::fill(a, a + mxl + 1, 0);
    }

    bool insert(int t) {
        n++;
        for (int j = mxl; j >= 0; j--) {
            int u = (t >> j) & 1;
            if (u == 0)
                continue;
            if (a[j])
                t ^= a[j];
            else {
                for (int k = 0; k < j; k++)
                    if ((t >> k) & 1)
                        t ^= a[k];
                for (int k = j + 1; k <= mxl; k++)
                    if ((a[k] >> j) & 1)
                        a[k] ^= t;
                a[j] = t;
                tot++;
                return true;
            }
        }
        return false;
    }

    int querymx(int x = 0) {  // 与x能异或出来的最大值，默认是x=0表示内部自己异或的最大值
        int ans = x;
        for (int i = mxl; i >= 0; i--) ans = max(ans, ans ^ a[i]);
        return ans;
    }
    int querymn(int x = 0) {  // 与x能异或出来的最小值，默认是x=0表示内部自己异或的最小值
        int ans = x;
        for (int i = mxl; i >= 0; i--) ans = min(ans, ans ^ a[i]);
        return ans;
    }

    void initkth() {
        static bool initialized = false;
        if (initialized)
            return;
        for (int i = 0; i <= mxl; i++) {
            if (a[i])
                tmp.push_back(a[i]);
        }
        deb(tmp);
        initialized = true;
    }
    // 第k小
    int querekthmin(int k, bool tkzo = false) {  // 第0小开始算
        initkth();
        int res = 0;
        if (tkzo == 0) {
            // 如果题目没有考虑空集，我们需要考虑能不能非空子集出现0
            if (tot == n)
                k++;
        }
        if (k >= (1LL << tot))
            return -1;
        for (int j = 0; j < tot; j++) {
            if ((k >> j) & 1)
                res ^= tmp[j];
        }
        return res;
    }
    // 值为x的下标
    int querypos(int x) {
        int l = 0, r = (1 << tot) - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (querekthmin(mid, true) >= x)
                r = mid;
            else
                l = mid + 1;
        }
        int res = qmi(2, n - tot) * l % mod + 1;
        res %= mod;
        return res;
    }
};