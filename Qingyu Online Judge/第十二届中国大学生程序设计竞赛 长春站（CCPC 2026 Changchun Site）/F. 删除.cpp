#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e9 + 7;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
vector<i64> fac, ifac;
auto init(int n)
{
    fac.resize(n + 1);
    ifac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto C(int n, int m) -> i64
{
    if (n < 0 || n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
struct Main
{
    int n;
    vector<int> a;
    vector<vector<vector<i64>>> f, g;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        f.resize(n + 5, vector<vector<i64>>(n + 5, vector<i64>(n + 5)));
        g.resize(n + 5, vector<vector<i64>>(n + 5, vector<i64>(n + 5)));
        for (int i = 0; i <= n; ++i)
        {
            f[i + 1][i][0] = 1;
            for (int j = 0; j <= n; ++j)
                g[i + 1][i][j] = 1;
        }
        for (int len = 1; len <= n; ++len)
            for (int i = 1, j; (j = i + len - 1) <= n; ++i)
            {
                for (int k = i; k <= j; ++k)
                    for (int t = 1; t <= n; ++t)
                        if (a[k] == -1 || (i == 1 || j == n ? 0 : t) == a[k])
                        {
                            auto now = g[i][k - 1][t - 1] * g[k + 1][j][t - 1] % mod;
                            if (t - 2 >= 0)
                                (now -= g[i][k - 1][t - 2] * g[k + 1][j][t - 2]) %= mod;
                            (f[i][j][t] += now * C(j - i, k - i)) %= mod;
                        }
                for (int t = 0; t <= n; ++t)
                    g[i][j][t] = ((t ? g[i][j][t - 1] : 0) + f[i][j][t]) % mod;
            }
        cout << (g[1][n][n] + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(100);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
