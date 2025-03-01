int qpow(int a, int k, int Mod) {
    using LL = long long;
    int ans = 1;
    while (k) {
        if (k & 1)
            ans = (LL)ans * a % Mod;
        a = (LL)a * a % Mod;
        k >>= 1;
    }
    return ans;
}