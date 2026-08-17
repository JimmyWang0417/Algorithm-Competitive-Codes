#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int base = 1e9 + 7;
auto _main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 5);
    vector<int> Log(n + 5);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        Log[i] = Log[i >> 1] + 1;
    }
    vector<vector<int>> f(Log[n] + 5, vector<int>(n + 5));
    vector<vector<u64>> g(Log[n] + 5, vector<u64>(n + 5));
    vector<u64> power(n + 5);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        f[0][i] = a[i];
        g[0][i] = 1;
        power[i] = power[i - 1] * base;
    }
    auto calc = [&](auto &&self, int l, int r, int maxx) -> u64
    {
        int p = l;
        for (int j = Log[n]; j >= 0; --j)
            if (p + (1 << j) - 1 <= r && f[j][p] < maxx)
                p += (1 << j);
        if (p > r)
            return 0;
        int k = Log[r - p + 1];
        return power[p - l] * g[k][p] + power[p + (1 << k) - l] * self(self, p + (1 << k), r, f[k][p]);
    };
    for (int j = 0; j < Log[n]; ++j)
        for (int i = 1; i + (2 << j) - 1 <= n; ++i)
        {
            f[j + 1][i] = max(f[j][i], f[j][i + (1 << j)]);
            g[j + 1][i] = g[j][i] + power[1 << j] * calc(calc, i + (1 << j), i + (2 << j) - 1, f[j][i]);
        }
    while (q--)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (calc(calc, l1, r1, 0) == calc(calc, l2, r2, 0) ? "Yes" : "No") << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
