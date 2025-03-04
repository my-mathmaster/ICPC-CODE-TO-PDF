db b[N][N];  // 增广矩阵
int id[N];   // id[j]=i：表示第j列的答案最终在第i行被计算
int rid[N];  // 第i行可以算出第j列的主元
void print(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + 1; j++) {
            cerr << setiosflags(ios::left) << setw(5) << b[i][j];
        }
        cerr << endl;
    }
    cerr << "---------------------" << endl;
}
int rksz;
int freenum;
vector<db> ans;
int gauss(db a[][N], int n, int m) {  // n个方程，m个未知数。默认多余自由变量为0，记录映射关系
    int r = 1;                        // 当前行
    for (int c = 1; c <= m; c++) {    // 消元进行到第c列
        // 1.找到c列的最大行t
        int t = r;
        for (int i = r; i <= n; i++)
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (t > n || fabs(a[t][c]) < eps)
            continue;  // c列已全为0
        assert(t <= n);
        // 2.把最大行换到上面
        for (int i = c; i <= m + 1; i++) swap(a[t][i], a[r][i]);
        // 3.把当前行r的第一个数，变成1
        for (int i = m + 1; i >= c; i--) a[r][i] /= a[r][c];
        // 4.把当前列c下面的所有数，全部消成0
        for (int i = r + 1; i <= n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = m + 1; j >= c; j--)
                    a[i][j] -= a[i][c] * a[r][j];
        id[c] = r;
        rid[r] = c;
        r++;  // 从下一行开始消元下一列
    }
    //---------------------------
    // print(n, m);
    rksz = r - 1;
    freenum = m - r + 1;
    ans.resize(m + 1);
    //------------------------
    if (r <= m) {  // 说明已经提前变成梯形矩阵
        for (int i = r; i <= n; i++) {
            if (fabs(a[i][m + 1]) > eps)
                return 0;  // 左边=0，右边≠0,无解
        }
    }
    for (int i = 1; i <= m; i++) {
        if (id[i] == 0) {
            // deb(i);
            ans[i] = 1;  // 如果第i列的主元没有对应行，自由变量随机赋值
        }
    }
    // 5.唯一解，从下往上回代，得到方程的解
    for (int i = rksz; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {  // 左侧自由变量残余，右侧已经算出来的以及右侧自由变量
            if (j == rid[i])
                continue;
            a[i][m + 1] -= a[i][j] * ans[j];
        }
        // deb(rid[i]);
        ans[rid[i]] = a[i][m + 1];  // 第i行的主元在rid[i]列
    }
    if (m > n) {
        return 2;
    } else {
        // m<=n;
        assert(rksz <= m);
        if (rksz == m)
            return 1;
        return 2;
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> b[i][j];
        }
    }
    for (int i = 1; i <= n; i++) cin >> b[i][m + 1];
    int t = gauss(b, n, m);  // n个方程,m个未知数
    deb(t, rksz, freenum);
    if (t == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 1; i <= m; i++) cout << fixed << setprecision(12) << ans[i] << endl;
    }
}