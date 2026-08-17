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
constexpr auto quickpow(i64 a, int b)
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
auto init(int m)
{
    fac.resize(m + 5), ifac.resize(m + 5);
    fac[0] = 1;
    for (int i = 1; i <= m; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[m] = quickpow(fac[m], mod - 2);
    for (int i = m; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto C(int x, int y)
{
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
struct Main
{
    int n, m;
    vector<vector<i64>> dp;
    Main()
    {
        cin >> n >> m;
        dp.assign(n + 5, vector<i64>(m + 5));
        for (int i = 0; i <= m; ++i)
            dp[0][i] = 1;
        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1];
            i64 t = 1;
            for (int j = 0; j <= m; ++j, (t *= i - 1) %= mod)
                (dp[i][j] += dp[i - 1][j] * t) %= mod;
        }
        i64 res = 0, t = 1;
        // for (int i = 1; i <= m; ++i)
        //     cout << dp[n][i] << ' ';
        // cout << '\n';
        init(max(n, m));
        for (int j = 1; j <= m; ++j)
        {
            (t *= ifac[n]) %= mod;
            (res += (j & 1 ? 1 : -1) * C(m, j) * (t * dp[n][j] % mod)) %= mod;
        }
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    // cin >> test;
    while (test--)
        Main();
    return 0;
}

