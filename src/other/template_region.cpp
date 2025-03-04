#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define deb(x) (void)(cerr << "L" << __LINE__ << ": " << #x << " = " << (x) << endl)
#else
#define deb(x)
#endif
#define ll long long
// #define int long long
#define baoliu(x, y) cout << fixed << setprecision(y) << x
#define endl "\n"
const int mod = 998244353;
const double eps = 1e-8;
const double PI = acos(-1.0);
void solve() {
    int n;
    cin >> n;
    cout << n << endl;
}
signed main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
#ifdef LOCAL
    double starttime = clock();
    auto t1 = freopen("in.txt", "r", stdin);
    auto t2 = freopen("out.txt", "w", stdout);
    assert(t1 != nullptr);
    assert(t2 != nullptr);
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