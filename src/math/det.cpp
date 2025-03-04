ll MOD;
int cal(vector<vector<int>>& a, int n) {
    ll flag = 1;
    // 转化成上三角矩阵
    for (int i = 1; i <= n; ++i) {  // 枚举行
        for (int k = i + 1; k <= n; ++k) {
            while (a[i][i]) {  // 辗转相除
                ll tim = a[k][i] / a[i][i];
                for (int j = i; j <= n; ++j)
                    a[k][j] = (a[k][j] - tim * a[i][j] % MOD + MOD) % MOD;
                swap(a[k], a[i]);  // 把较小的放上去
                flag = -flag;
            }
            swap(a[k], a[i]);
            flag = -flag;
        }
    }
    ll res = 1;
    for (int i = 1; i <= n; ++i)
        res = res * a[i][i] % MOD;
    res *= flag;
    return (res + MOD) % MOD;
}
void solve() {
    int n;
    cin >> n >> MOD;
    vector b(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> b[i][j];
    ll ans = cal(b, n);
    cout << ans << endl;
}
