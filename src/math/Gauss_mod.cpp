#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 205;
int n, m;
int s[N], t[N], G[N][N];
int a[N][N];
void swap_line(int x, int y) {
    for (int i = 1; i <= n + 1; i++) swap(a[x][i], a[y][i]);
}
bool empty_line(int x, int y) {
    for (int i = x; i <= n; i++)
        if (a[i][y])
            return 0;
    return 1;
}
void exgcd(int n, int m, int &x, int &y) {
    if (m == 0) {
        x = 1, y = 0;
        return;
    }
    int x1, y1;
    exgcd(m, n % m, x1, y1);
    x = y1, y = x1 - n / m * y1;
}
int get_inv(int p) {
    int x, y;
    exgcd(p, m, x, y);
    return (x % m + m) % m;
}
void gauss() {
    int hang = 1, pos;
    for (int i = 1; i <= n; i++) {
        pos = hang;
        if (empty_line(pos, i))
            continue;
        for (int j = hang; j <= n; j++) {
            if (a[j][i] > a[pos][i])
                pos = j;
        }
        swap_line(hang, pos);
        int op = get_inv(a[hang][i]);
        for (int j = 1; j <= n; j++) {
            if (hang == j)
                continue;
            for (int k = n + 1; k >= i; k--) a[j][k] = (a[j][k] - (a[hang][k] * a[j][i] % m + m) % m * op % m + m) % m;
        }
        hang++;
    }
    if (hang <= n) {
        for (int i = hang; i <= n; i++) {
            bool flag = 0;
            for (int j = 1; j <= n; j++)
                if (a[i][j])
                    flag = 1;
            if (!flag && a[i][n + 1]) {
                cout << "niuza";
                return;
            }
        }
    }
    hang = 1;
    for (int i = 1; i <= n; i++) {
        cout << a[hang][n + 1] * get_inv(a[hang][i]) % m << " ";
        a[hang][n + 1] = 0;
        if (!a[hang][i + 1])
            hang++;
    }
}
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int u;
            cin >> u;
            G[i][u] = 1;
        }
    }
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int u = 1; u <= n; u++) {
        a[u][u] = 1;  //!@!!!
        for (int v = 1; v <= n; v++) {
            if (G[v][u])
                a[u][v] = 1;
        }
        a[u][n + 1] = ((t[u] - s[u]) % m + m) % m;
    }
    gauss();
    return 0;
}