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
    int n, m, q, s, t;
    int limit;
    template <typename T>
    auto FWT(vector<T> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    (dp[i + j + mid] += dp[i + j]) %= mod;
    }
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
    vector<int> id;
    vector<vector<int>> e;
    Main()
    {
        cin >> n >> m >> s >> t;

        id.resize(n + 5);
        for (int i = 1, j = 0; i <= n; ++i)
        {
            if (i == s || i == t)
                continue;
            id[i] = j++;
        }
        id[s] = n - 2, id[t] = n - 1;
        e.resize(n, vector<int>(n));
        n -= 2;
        limit = 1 << n;

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            e[id[u]][id[v]]++;
        }

        vector<vector<i64>> dp(limit, vector<i64>(n));
        for (int i = 0; i < n; ++i)
            dp[1 << i][i] = e[i][n + 1];
        vector<vector<i64>> f(limit, vector<i64>(n + 1));
        for (int S = 0; S < limit; ++S)
            for (int i = 0; i < n; ++i)
            {
                if (!dp[S][i])
                    continue;
                for (int j = 0; j < n; ++j)
                {
                    if ((S >> j) & 1)
                        continue;
                    (dp[S | (1 << j)][j] += dp[S][i] * e[j][i]) %= mod;
                }
                f[S][__builtin_popcount(S)] += dp[S][i] * e[n][i] % mod;
            }
        FWT(f);

        vector<i64> inv(n + 5);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;

        for (int S = 0; S < limit; ++S)
        {
            vector<i64> g(n + 1);
            g[0] = 1;
            for (int i = 1; i <= n; ++i)
            {
                i64 res = 0;
                for (int j = 1; j <= i; ++j)
                    (res += j * f[S][j] % mod * g[i - j]) %= mod;
                g[i] = res * inv[i] % mod;
            }
            f[S] = g;
        }

        IFWT(f);
        vector<i64> g(limit);
        for (int i = 0; i < limit; ++i)
            g[i] = f[i][__builtin_popcount(i)];
        FWT(g);
        vector<i64> answer(n + 2);
        auto times = quickpow(2, e[n][n + 1]);
        for (int i = 0; i < n; ++i)
        {
            for (int S = 1 << i; S < limit; S = (S + 1) | (1 << i))
            {
                if (!dp[S][i])
                    continue;
                (answer[i] += dp[S][i] * e[n][i] % mod * times % mod * g[(limit - 1) ^ S]) %= mod;
            }
        }
        answer[n + 1] = g[limit - 1] * (times - 1) % mod;
        cin >> q;
        while (q--)
        {
            int x;
            cin >> x;
            cout << (answer[id[x]] + mod) % mod << '\n';
        }
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