#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using LL = long long;

template <class S>
inline bool updmn(S &x, const S y) {
    if (y < x) {
        x = y;
        return 1;
    }
    return 0;
}

struct Main {
    int n;
    vector<int> a;
    void main() {
        read();
        if (n == 1) {
            cout << a[0] << "\n";
            return;
        }
        LL ans = solve();
        vector<int> b(a.size());
        b[0] = a[0];
        for (int i = 1; i < n; ++i) b[i] = a.end()[-i];
        a = b;
        updmn(ans, solve());
        cout << ans << "\n";
    }
    void read() {
        cin >> n;
        a.assign(n, 0);
        for (auto &x : a) cin >> x;
    }
    LL solve() const {
        dbg(a);
        LL res = LL(1e17), base = a[0];
        for (int i = 1; i < n; ++i) {
            const LL tmp = base + 1ll * (n - i) * (a[i - 1] + a[i]);
            dbg(i, base, tmp);
            updmn(res, tmp);
            base += a[i - 1] + a[i];
        }
        return res;
    }
};
signed main() {
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    int T;
    cin >> T;
    while (T--)
        Main{}.main();
    return 0;
}
