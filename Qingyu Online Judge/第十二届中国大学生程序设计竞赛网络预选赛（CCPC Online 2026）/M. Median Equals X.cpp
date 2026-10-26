#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define int long long
#define all(x) (x).begin(), (x).end()
using LL = long long;
using ai2 = array<int, 2>;

template <class S>
inline bool updmx(S &x, const S y) {
    if (x < y) {
        x = y;
        return 1;
    }
    return 0;
}

constexpr int MOD = 998244353;
LL ksm(LL a, LL b) {
    a %= MOD;
    LL r = 1;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}
inline void madd(LL &x, const LL y) {
    if ((x += y) >= MOD) x -= MOD;
}
inline void msub(LL &x, const LL y) {
    if ((x -= y) < 0) x += MOD;
}

constexpr int N = LL(1e6);
LL fc[N], fc_inv[N];
const bool __init_fc = []() -> bool {
    fc[0] = fc_inv[0] = 1;
    for (int i = 1; i < N; ++i)
        fc[i] = fc[i - 1] * i % MOD;
    fc_inv[N - 1] = ksm(fc[N - 1], MOD - 2);
    for (int i = N - 2; i > 0; --i)
        fc_inv[i] = fc_inv[i + 1] * (i + 1) % MOD;
    return 1;
}();

LL C(const int n, const int m) {
    if (n == m) return 1;
    if (n < 0 || m < 0 || n - m < 0) return 0;
    return fc[n] * fc_inv[m] % MOD * fc_inv[n - m] % MOD;
}
LL calc(const int n, const int m) {
    LL x = C(n + m, n);
    return x;
}
// C(n,n) + ... + C(n+m,n)
LL calc2(const int m, const int n) {
#ifdef LOCAL
    #include <cassert>
    LL res = 0;
    for (int x = n; x <= n + m; ++x) madd(res, C(x, n));
    assert(res == C(n + m + 1, n + 1));
    dbg("! res = %lld | C(%d, %d) = %lld\n",
        res, n + m + 1, n + 1, C(n + m + 1, n + 1));
#endif
    return C(n + m + 1, n + 1);
}

struct Main {
    int n, X;
    vector<int> a;
    map<int, ai2> rg;
    LL ans = 0;
    void main() {
        cin >> n >> X;
        a.assign(n, 0);
        for (auto &x : a) cin >> x;
        sort(all(a));
        {
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && a[j] == a[i]) ++j;
                rg[a[i]] = {i, j - 1};
                i = j;
            }
        }
#ifdef LOCAL
        dbg("* ");
        for (int i = 0; i < n; ++i) dbg("%d ", a[i]);
        dbg("\n");
        for (auto [x, v] : rg) dbg("* %d [%d, %d]\n", x, v[0], v[1]);
#endif
        // odd
        for (int i = 0; i < n; ++i) {
            if (a[i] != X) continue;
            madd(ans, calc(i, n - i - 1));
        }
        // even
        for (int i = 0; i < n; ++i) {
            const int x = a[i];
            const int y = X * 2 - x;
            if (y < x) break;
            auto it = rg.find(y);
            if (it == rg.end()) continue;
            const auto [l, r] = [&]() -> ai2 {
                auto [_l, _r] = it->second;
                updmx(_l, i + 1);
                return ai2{_l, _r};
            }();
            if (l > r) continue;
            const int m1 = n - r - 1;
            const int m2 = n - l - 1;
            LL add = calc2(m2, i);
            msub(add, calc2(m1 - 1, i));
            madd(ans, add);
            dbg("i = %d [%d, %d] m1 = %d m2 = %d add = %lld\n",
                i, l, r, m1, m2, add);
        }
        cout << ans << "\n";
    }
};

signed main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
