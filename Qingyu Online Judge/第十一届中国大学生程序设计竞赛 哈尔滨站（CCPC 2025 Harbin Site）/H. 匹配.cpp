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
constexpr int mod = 998244353;
template <typename T = int>
auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
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
auto gause(int m, vector<vector<i64>> &g)
{
    for (int i = 1; i <= m; ++i)
    {
        int where = i;
        for (int j = i; j <= m; ++j)
            if (g[j][i])
            {
                where = j;
                break;
            }
        if (where != i)
            swap(g[where], g[i]);
        auto inv = quickpow(g[i][i]);
        for (int j = i; j <= m + 1; ++j)
            (g[i][j] *= inv) %= mod;
        for (int j = i + 1; j <= m; ++j)
        {
            for (int k = i + 1; k <= m + 1; ++k)
                (g[j][k] -= g[j][i] * g[i][k]) %= mod;
            g[j][i] = 0;
        }
    }
    for (int i = m; i >= 1; --i)
        for (int j = i + 1; j <= m; ++j)
        {
            (g[i][m + 1] -= g[i][j] * g[j][m + 1]) %= mod;
            g[i][j] = 0;
        }
}
vector<i64> fac, ifac;
auto initcomb(int m)
{
    fac.resize(m + 5);
    ifac.resize(m + 5);
    fac[0] = 1;
    for (int i = 1; i <= m; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[m] = quickpow(fac[m]);
    for (int i = m; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto C(int n, int m) -> i64
{
    if (n < 0 || n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
auto A(int n, int m) -> i64
{
    if (n < 0 || n < m)
        return 0;
    return fac[n] * ifac[n - m] % mod;
}
struct Main
{
    int n, m;
    Main()
    {
        cin >> n >> m;
        vector a(2 * m + 5, vector<i64>(2 * m + 5));
        auto all = quickpow(C(2 * m, m) * A(m, m));
        for (int i = 1; i <= m * 2; ++i)
        {
            vector<i64> f(m + 1);
            for (int j = 0; j <= m; ++j)
            {
                int x = i - (m - j), y = (2 * m - i) - (m - j);
                for (int k = 0; k <= j; ++k)
                {
                    (f[j] += (C(x, k) * A(x - k, k) % mod) *
                             (C(y, j - k) * A(y - (j - k), j - k) % mod)) %= mod;
                }
            }
            for (int j = max(1, i - m); j <= min(2 * m, i + m); ++j)
            {
                int ij = abs(i - j);
                for (int l = ij; l <= m; ++l)
                {
                    int x = l, y = l - ij, z = m - x - y;
                    // C(i, x) * C(m - i, x);
                    // C(i - x, y) * C(m - i - x, y);
                    // f(z)
                    if (0 <= z && z <= m)
                        (a[i][j] += (C(i, x) * A(2 * m - i, x) % mod) *
                                    (C(i - x, y) * A(2 * m - i - x, y) % mod) % mod *
                                    f[z]) %= mod;
                }
                (a[i][j] *= all) %= mod;
            }
        }
        vector p(2 * m + 5, vector<i64>(2 * m + 5));
        for (int i = 1; i < 2 * m; ++i)
        {
            p[i][i] = 1;
            for (int j = 1; j <= 2 * m; ++j)
                (p[i][j] -= a[i][j]) %= mod;
        }
        p[2 * m][2 * m] = 1, p[2 * m][2 * m + 1] = 1;
        gause(2 * m, p);
        vector dp(2 * m + 5, vector<i64>(2 * m + 5));
        for (int i = 1; i < 2 * m; ++i)
        {
            auto inv = quickpow(p[i][2 * m + 1]);
            dp[i][i] = 1;
            for (int j = max(1, i - m); j <= min(2 * m, i + m); ++j)
                (dp[i][j] -= a[i][j] * p[j][2 * m + 1] % mod * inv) %= mod;
            dp[i][2 * m + 1] = 1;
        }
        dp[2 * m][2 * m] = 1;
        gause(2 * m, dp);
        i64 res = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            (res += p[x][2 * m + 1] * dp[x][2 * m + 1]) %= mod;
        }
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    initcomb(1e5);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
