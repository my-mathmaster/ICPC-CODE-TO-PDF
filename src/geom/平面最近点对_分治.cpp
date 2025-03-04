#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define deb(...)
#endif
using namespace std;
#define ll long long
// #define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define db long double
#define baoliu(x, y) cout << fixed << setprecision(y) << x
#define endl "\n"
#define alls(x) (x).begin(), (x).end()
#define fs first
#define sec second
#define bug(x) cerr << #x << " = " << x << endl
const int N = 2e6 + 10;
const int M = 1e6 + 10;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-8;
const double PI = acos(-1.0);
int n;
struct node {
    db x, y;
    bool operator<(const node &A) const {
        return x < A.x;
    }
} a[N], c[N];
db dis(node c, node d) {
    db c1 = c.x - d.x, c2 = c.y - d.y;
    return sqrt(c1 * c1 + c2 * c2);
}
db cal(int l, int r) {
    if (l == r)
        return 1e12;
    int cnt = 0;
    int mid = (l + r) >> 1;
    db d = min(cal(l, mid), cal(mid + 1, r));
    for (int i = l; i <= r; i++) {
        if (fabs(a[i].x - a[mid].x) < d) {
            c[++cnt].y = a[i].x;
            c[cnt].x = a[i].y;
        }
    }
    sort(c + 1, c + 1 + cnt);
    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j <= cnt && fabs(c[j].y - c[i].y) < d; j++) {
            d = min(d, dis(c[i], c[j]));
        }
    }
    return d;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + 1 + n);
    db ans = cal(1, n);
    baoliu(ans, 12);
}

signed main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
#ifdef LOCAL
    double starttime = clock();
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while (t--) solve();
#ifdef LOCAL
    double endtime = clock();
    cerr << "Time Used: " << (double)(endtime - starttime) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
#endif
    return 0;
}