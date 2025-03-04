int gauss(vector<vector<db>>& a, int n) {
    int r = 1;                      // 当前行
    for (int c = 1; c <= n; c++) {  // 消元进行到第c列
        // 1.找到c列的最大行t
        int t = r;
        for (int i = r; i <= n; i++)
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;
        if (fabs(a[t][c]) < eps)
            continue;  // c列已全为0

        // 2.把最大行换到上面
        for (int i = c; i <= n + 1; i++) swap(a[t][i], a[r][i]);

        // 3.把当前行r的第一个数，变成1
        for (int i = n + 1; i >= c; i--) a[r][i] /= a[r][c];

        // 4.把当前列c下面的所有数，全部消成0
        for (int i = r + 1; i <= n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = n + 1; j >= c; j--)
                    a[i][j] -= a[i][c] * a[r][j];
        r++;  // 从下一行开始消元下一列
    }
    if (r <= n) {  // 说明已经提前变成梯形矩阵
        for (int i = r; i <= n; i++) {
            if (fabs(a[i][n + 1]) > eps)
                return 0;
        }  // 左边=0，右边≠0,无解
        return 2;  // 0==0，无穷多解
    }
    // 5.唯一解，从下往上回代，得到方程的解
    for (int i = n; i >= 1; i--)
        for (int j = i + 1; j <= n; j++)
            a[i][n + 1] -= a[i][j] * a[j][n + 1];
    return 1;
}

void solve() {
    int n;
    cin >> n;
    vector b(n + 1, vector<db>(n + 2));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> b[i][j];
    int t = gauss(b, n);
    if (t == 0) {
        cout << "No solution " << endl;
    } else if (t == 2) {
        cout << "Infinite group solutions" << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            baoliu(b[i][n + 1], 2);
            cout << endl;
        }
    }
}