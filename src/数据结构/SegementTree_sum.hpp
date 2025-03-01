#include <vector>

template <typename T>
class SegmentTree_sum {
    int ssize;
    struct node {
        T sum = 0, add = 0;
    };
    std::vector<node> tr;

    void Pushup(int u) {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }

    void Pushdown(int u, int l, int r) {
        auto &add = tr[u].add;
        int mid = (l + r) >> 1;
        tr[u << 1].sum += add * (mid - l + 1);
        tr[u << 1 | 1].sum += add * (r - mid);
        tr[u << 1].add += add;
        tr[u << 1 | 1].add += add;
        tr[u].add = 0;
    }
    template <typename TT>
    void Build(int u, int l, int r, std::vector<TT> &w) {
        if (l == r) {
            tr[u].sum = w[l];
            return;
        }

        int mid = (l + r) >> 1;
        Build(u << 1, l, mid, w);
        Build(u << 1 | 1, mid + 1, r, w);
        Pushup(u);
    }
    void Modify(int L, int R, T add, int u, int l, int r) {
        if (l >= L && r <= R) {
            tr[u].sum += (r - l + 1) * add, tr[u].add += add;
            return;
        }
        if (tr[u].add)
            Pushdown(u, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid)
            Modify(L, R, add, u << 1, l, mid);
        if (R > mid)
            Modify(L, R, add, u << 1 | 1, mid + 1, r);
        Pushup(u);
    }
    T Query(int L, int R, int u, int l, int r) {
        if (l >= L && r <= R)
            return tr[u].sum;
        if (tr[u].add)
            Pushdown(u, l, r);
        int mid = (l + r) >> 1;
        T sum = 0;
        if (L <= mid)
            sum += Query(L, R, u << 1, l, mid);
        if (R > mid)
            sum += Query(L, R, u << 1 | 1, mid + 1, r);
        return sum;
    }

public:
    template <typename TT>
    /// @brief 有初值的初始化
    /// @param w vector<TT> 数据从[1]开始存放
    SegmentTree_sum(std::vector<TT> &w) {
        ssize = w.size() - 1;
        tr.resize(4 * w.size());
        Build(1, 1, w.size() - 1, w);
    }
    /// @brief 全设为0的初始化
    /// @param n 树的大小
    SegmentTree_sum(int n) {
        ssize = n;
        tr.resize(4 * n + 10);
    }

    /// @brief 区间修改
    /// @param L 区间左端
    /// @param R 区间右端
    /// @param add 修改
    void modify(int L, int R, T add) {
        L = std::max(1, L);
        R = std::min(R, ssize);
        Modify(L, R, add, 1, 1, ssize);
    }

    /// @brief 单点修改
    /// @param D 被修改点
    /// @param add 修改
    void modify(int D, T add) {
        if (D < 1 || D > ssize)
            return;
        Modify(D, D, add, 1, 1, ssize);
    }

    /// @brief 区间查询
    /// @param L 区间左端点
    /// @param R 区间右端点
    /// @return 区间和
    T query(int L, int R) {
        L = std::max(1, L);
        R = std::min(R, ssize);
        return Query(L, R, 1, 1, ssize);
    }

    /// @brief 单点查询
    /// @param D 查询点
    /// @return 单点值
    T query(int D) {
        if (D < 1 || D > ssize)
            return 0;
        return Query(D, D, 1, 1, ssize);
    }
};