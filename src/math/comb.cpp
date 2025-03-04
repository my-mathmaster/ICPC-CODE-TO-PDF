#define int long long
int fac[N], infac[N], inv[N];
int qmi(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (res * a) % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int askinv(int x) {
    return qmi(x, mod - 2);
}
void init(int n) {
    fac[0] = 1, infac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    infac[n] = askinv(fac[n]);
    for (int i = n; i >= 1; i--) {
        infac[i - 1] = infac[i] * i % mod;
        inv[i] = fac[i - 1] * infac[i] % mod;
    }
}
int C(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    return fac[n] * infac[m] % mod * infac[n - m] % mod;
}

int A(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    return fac[n] * infac[n - m] % mod;
}