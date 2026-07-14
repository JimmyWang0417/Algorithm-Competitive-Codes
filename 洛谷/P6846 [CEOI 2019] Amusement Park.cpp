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
constexpr int inv2 = quickpow(2);
struct Main
{
    int n, m;
    int limit;
    template <typename T>
    auto FWT(vector<vector<T>> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        (dp[i + j + mid][k] += dp[i + j][k]) %= mod;
    }
    template <typename T>
    auto IFWT(vector<vector<T>> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        (dp[i + j + mid][k] -= dp[i + j][k]) %= mod;
    }
    vector<int> F, G;
    vector<vector<i64>> f;

    Main()
    {
        cin >> n >> m;
        limit = 1 << n;
        F.resize(n);
        G.resize(limit);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            F[u - 1] |= 1 << (v - 1);
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < (1 << i); ++j)
                G[(1 << i) | j] = F[i] | G[j];
        f.resize(limit, vector<i64>(n + 1));
        for (int S = 1; S < limit; ++S)
        {
            if (S & G[S])
                continue;
            int p = __builtin_popcount(S);
            f[S][p] = p & 1 ? 1 : -1;
        }
        FWT(f);
        for (int S = 0; S < limit; ++S)
        {
            vector<i64> g(n + 1);
            g[0] = 1;
            for (int i = 1; i <= n; ++i)
                for (int j = 0; j < i; ++j)
                    (g[i] += g[j] * f[S][i - j]) %= mod;
            f[S] = g;
        }
        IFWT(f);
        cout << (f[limit - 1][n] * m % mod * inv2 % mod + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}