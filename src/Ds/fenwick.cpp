template <typename T>
struct Fwk {
    int n;
    std::vector<T> a;

    Fwk(int n_ = 0) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        a.assign(n + 1, T{});
    }

    void add(int x, const T &v) {
        assert(x > 0);
        for (int i = x; i <= n; i += i & -i) {
            a[i] = a[i] + v;
        }
    }

    T sum(int x) {
        T ans{};
        assert(x <= n);
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i];
        }
        return ans;
    }

    T rangeSum(int l, int r) {  // 要传入l-1
        return sum(r) - sum(l);
    }

    int select(const T &k) {  // 寻找最后一个使得前缀和小于等于 k 的位置。
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {  // GCC
            if (x + i <= n && cur + a[x + i] <= k) {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};