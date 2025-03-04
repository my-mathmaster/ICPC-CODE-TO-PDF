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
#define db double
#define baoliu(x, y) cout << fixed << setprecision(y) << x
#define endl "\n"
#define alls(x) (x).begin(), (x).end()
#define fs first
#define sec second
#define bug(x) cerr << #x << " = " << x << endl
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-8;
const double PI = acos(-1.0);
struct treehash {
    int n;
    int rt = 0;         // 注意无向树的根怎么给
    vector<ll> h1, h2;  // hash的值在longlong范围内
    vector<int> siz;
    vector<vector<int>> e;
    treehash(int n_) : n(n_), h1(n_ + 1), h2(n_ + 1), siz(n_ + 1), e(n_ + 1) {}
    ll h(ll x) {
#pragma GCC diagnostic ignored "-Woverflow"
        return x * x * x * 1237123 + 19260817;
    }

    ll f(ll x) {
        ll cur = h(x & ((1 << 31) - 1)) + h(x >> 31);
        return cur;
    }
    void add(int u, int v) {
        e[u].push_back(v);
    }
    int pos = 0, pos2 = 0, ans = 1e9;
    void getroot(int u, int fa) {  // 找树的1-2重心
        siz[u] = 1;
        int mx = 0;
        for (auto v : e[u]) {
            if (v == fa)
                continue;
            getroot(v, u);
            siz[u] += siz[v];
            mx = max(mx, siz[v]);
        }
        mx = max(mx, n - siz[u]);
        // 维护了重心是pos
        if (mx < ans) {
            ans = mx, pos = u, pos2 = 0;
        } else if (mx == ans) {
            pos2 = u;
        }
    };
    void dfs1(int u, int fa, auto &h) {
        h[u] = 1;
        for (auto v : e[u]) {
            if (v == fa)
                continue;
            dfs1(v, u, h);
            h[u] += f(h[v]);
        }
    };
    ll work() {  // 无根树先找重心
        getroot(rt, 0);
        dfs1(pos, 0, h1);
        if (pos2)
            dfs1(pos2, 0, h2);
        ll val = h1[pos];
        if (pos2) {
            val = max(val, h2[pos2]);
        }
        return val;
    }
};
void solve() {
    int n;
    cin >> n;
    treehash h1(n), h2(n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        h1.add(u, v);
        h1.add(v, u);
    }
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        h2.add(u, v);
        h2.add(v, u);
    }
    h1.dfs1(1, 0, h1.h1);
    h2.dfs1(1, 0, h2.h1);

    if (h1.h1[1] == h2.h1[1])
        cout << "Isomorphism" << endl;
    else
        cout << "No" << endl;
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
    cin >> t;
    while (t--) solve();
#ifdef LOCAL
    double endtime = clock();
    cerr << "Time Used: " << (double)(endtime - starttime) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
#endif
    return 0;
}