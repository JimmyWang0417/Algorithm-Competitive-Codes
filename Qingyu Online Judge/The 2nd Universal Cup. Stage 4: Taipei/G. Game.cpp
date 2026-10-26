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
    fac.resize(n + 1), ifac.resize(n + 1);
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
    vector<array<int, 5>> L, R;
    array<array<array<array<array<int, 26>, 26>, 26>, 26>, 26> dp;
    vector<i64> f, g;
    Main()
    {
        cin >> n;
        L.resize(n), R.resize(n);
        for (int i = 0; i < n; ++i)
        {
            string s, t;
            cin >> s >> t;
            for (int j = 0; j < 5; j++)
            {
                if (t[j] == '<')
                {
                    L[i][j] = 0;
                    R[i][j] = s[j] - 'A';
                }
                else if (t[j] == '=')
                {
                    L[i][j] = s[j] - 'A';
                    R[i][j] = s[j] - 'A' + 1;
                }
                else
                {
                    L[i][j] = s[j] - 'A' + 1;
                    R[i][j] = 26;
                }
            }
        }
        f.resize(n + 5), g.resize(n + 5);
        for (int mask = 0; mask < (1 << 5); ++mask)
        {
            dp.fill({});
            for (int i = 0; i < n; ++i)
            {
                array<int, 5> p = {};
                auto dfs = [&](auto &&self, int u, int c) -> void
                {
                    if (u == 5)
                    {
                        dp[p[0]][p[1]][p[2]][p[3]][p[4]] += c;
                        return;
                    }
                    int t = (mask >> u) & 1;
                    if (L[i][u] < R[i][u] - t)
                    {
                        p[u] = L[i][u];
                        self(self, u + 1, c);
                        if (R[i][u] - t < 26)
                        {
                            p[u] = R[i][u] - t;
                            self(self, u + 1, -c);
                        }
                    }
                };
                dfs(dfs, 0, 1);
            }
            for (int i = 0; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    for (int k = 0; k < 26; ++k)
                        for (int l = 0; l < 26; ++l)
                            for (int r = 1; r < 26; ++r)
                                dp[i][j][k][l][r] += dp[i][j][k][l][r - 1];
            for (int i = 0; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    for (int k = 0; k < 26; ++k)
                        for (int l = 1; l < 26; ++l)
                            for (int r = 0; r < 26; ++r)
                                dp[i][j][k][l][r] += dp[i][j][k][l - 1][r];
            for (int i = 0; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    for (int k = 1; k < 26; ++k)
                        for (int l = 0; l < 26; ++l)
                            for (int r = 0; r < 26; ++r)
                                dp[i][j][k][l][r] += dp[i][j][k - 1][l][r];
            for (int i = 0; i < 26; ++i)
                for (int j = 1; j < 26; ++j)
                    for (int k = 0; k < 26; ++k)
                        for (int l = 0; l < 26; ++l)
                            for (int r = 0; r < 26; ++r)
                                dp[i][j][k][l][r] += dp[i][j - 1][k][l][r];
            for (int i = 1; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    for (int k = 0; k < 26; ++k)
                        for (int l = 0; l < 26; ++l)
                            for (int r = 0; r < 26; ++r)
                                dp[i][j][k][l][r] += dp[i - 1][j][k][l][r];
            int c = __builtin_parity(mask) ? -1 : 1;
            for (int i = 0; i < 26; ++i)
                for (int j = 0; j < 26; ++j)
                    for (int k = 0; k < 26; ++k)
                        for (int l = 0; l < 26; ++l)
                            for (int r = 0; r < 26; ++r)
                                f[dp[i][j][k][l][r]] += c;
        }
        g[0] = 1;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= i; ++j)
                (g[j] += f[i] * C(i, j)) %= mod;
        for (int i = 1; i <= n; i++)
        {
            auto res = (g[i - 1] * fac[i - 1] % mod * (n - i + 1) - g[i] * fac[i]) % mod;
            cout << (res + mod) % mod << ' ';
        }
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(1e5);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
