#include <bits/stdc++.h>

using namespace std;

const int N = 6e5 + 10, M = N * 25 + N;

// 数组大小应为，点数 × 层数（长度），然后第二维是看可能的分支数量。
int idx, tr[M][2], cnt[M], root[N], val[M];
int n, m, a[N];

void insert(int i, int x) {
    int p = root[i], q = root[i - 1];
    for (int k = 24; k >= 0; k--) {
        int t = x >> k & 1;
        if (tr[q][t ^ 1])
            tr[p][t ^ 1] = tr[q][t ^ 1];
        if (tr[p][t]) {
            p = tr[p][t];
            q = tr[q][t];
        } else {
            p = tr[p][t] = ++idx;
            q = tr[q][t];
        }
        cnt[p] = cnt[q] + 1;
    }
    val[p] = x;
}
int query(int l, int r, int x) {
    int p = root[r], q = root[max(0, l - 1)];
    for (int k = 24; k >= 0; k--) {
        int t = x >> k & 1;
        if (tr[p][t ^ 1] && cnt[tr[p][t ^ 1]] - cnt[tr[q][t ^ 1]] > 0) {
            p = tr[p][t ^ 1], q = tr[q][t ^ 1];
        } else {
            p = tr[p][t], q = tr[q][t];
        }
    }
    return x ^ val[p];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        root[i] = ++idx;
        a[i] ^= a[i - 1];
        insert(i, a[i]);
    }
    while (m--) {
        char op;
        int l, r, x;
        cin >> op;
        if (op == 'A') {
            cin >> x;
            root[++n] = ++idx;
            a[n] = a[n - 1] ^ x;
            insert(n, a[n]);
        } else {
            cin >> l >> r >> x;
            int y = a[n] ^ x;
            cout << query(l - 1, r - 1, y) << '\n';
        }
    }
    return 0;
}