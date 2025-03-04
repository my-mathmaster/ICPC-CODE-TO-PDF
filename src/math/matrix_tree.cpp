int cal(vector<vector<int>>& a, int n) {//针对没有逆元
    ll flag = 1;
    // 转化成上三角矩阵
    for (int i = 1; i <= n; ++i) {  // 枚举行
        for (int k = i + 1; k <= n; ++k) {
            while (a[i][i]) {  // 辗转相除
                ll tim = a[k][i] / a[i][i];
                for (int j = i; j <= n; ++j)
                    a[k][j] = (a[k][j] - tim * a[i][j]);
                swap(a[k], a[i]);  // 把较小的放上去
                flag = -flag;
            }
            swap(a[k], a[i]);
            flag = -flag;
        }
    }
    ll res = 1;
    for (int i = 1; i <= n; ++i)
        res = res * a[i][i];
    res *= flag;
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> b(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        b[u][u]++;
        b[v][v]++;
        b[u][v]--;
        b[v][u]--;
    }
    int ans = cal(b, n - 1);
    cout << ans << endl;
}