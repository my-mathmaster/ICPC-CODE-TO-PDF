int rksz;
// 还没有处理n方程，m变量的情况(n>m)
int gauss(vector<vector<int>>& a, int n, int m, vector<int>& solution) {
    vector<int> freevar;           // 记录自由变量对应的列
    vector<int> pivot(n + 1, -1);  // 记录每一行的主元所在的列
    int r = 1;
    for (int c = 1; c <= m; c++) {
        int t = r;
        // 找到当前列中的主元
        for (int i = r; i <= n; i++) {
            if (a[i][c]) {
                t = i;
                break;
            }
        }
        // if (t > n)
        //     deb(t, n, c, m);
        // assert(t <= n);
        // assert(c <= m);
        if (t > n || !a[t][c]) {
            freevar.push_back(c);
            continue;  // 当前列没有主元，继续到下一列
        }
        pivot[r] = c;  // 第 r 行的主元在 c 列
        if (t != r) {  // 交换行，将主元行放在第 r 行
            for (int i = c; i <= m + 1; i++)
                swap(a[r][i], a[t][i]);
        }
        // 消去主元下方的所有行
        for (int i = r + 1; i <= n; i++) {
            if (a[i][c])
                for (int j = m + 1; j >= c; j--) a[i][j] ^= a[r][j];
        }
        r++;
    }

    // 检查是否有解
    for (int i = r; i <= n; i++) {
        if (a[i][m + 1])
            return 0;  // 无解
    }
    // int tot = 0;
    rksz = r - 1;  // 这是系数矩阵的秩
    // 自由变量根据题目要求情况去赋值
    for (auto i : freevar) solution[i] = 0;
    //------------------------------
    for (int i = rksz; i >= 1; i--) {
        int sum = a[i][m + 1];
        for (int j = 1; j <= m; j++) {
            if (j == pivot[i]) {
                continue;
            }  // 如果不是主元所在的列
            sum ^= (a[i][j] * solution[j]);  // 右边已经求出来的，左边自由变量遗留
        }
        solution[pivot[i]] = sum;  // 求解对应的主元变量
    }
    // assert(rksz <= m);
    if (rksz < m)
        return 2;  // 无穷多解
    return 1;      // 唯一解
}
// int t = gauss(b, n，m, sol);