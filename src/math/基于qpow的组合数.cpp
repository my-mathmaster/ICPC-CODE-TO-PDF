#include <vector>

int qpow(int a, int k, int M) {
    using LL = long long;
    int ans = 1;
    while (k) {
        if (k & 1)
            ans = (LL)ans * a % M;
        a = (LL)a * a % M;
        k >>= 1;
    }
    return ans;
}

std::vector<int> inv, in;
void q_inv(int n, int M) {
    inv.resize(n + 10), in.resize(n + 10);
    in[0] = in[1] = inv[0] = 1;
    for (long long i = 2; i <= n; i++) {
        in[i] = in[i - 1] * i % M;
    }
    inv[n] = qpow(in[n], M - 2, M);
    for (long long i = n; i > 1; i--) {
        inv[i - 1] = inv[i] * i % M;
    }
}

/// @brief 组合数C_a^b mod M
/// @param a 下标
/// @param b 上标
/// @param M 模
/// @return rt
inline int C_q(int a, int b, int M) {
    return 1LL * in[a] * inv[a - b] % M * inv[b] % M;
}