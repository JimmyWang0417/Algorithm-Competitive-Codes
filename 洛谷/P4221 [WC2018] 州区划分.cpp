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
struct Main
{
    constexpr static int inv2 = quickpow(2);
    int n, m, p;
    int limit;
    auto FWT(vector<i64> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                {
                    auto x = dp[i + j], y = dp[i + j + mid];
                    dp[i + j] = (x + y) % mod;
                    dp[i + j + mid] = (x - y) % mod;
                }
    }
    auto IFWT(vector<i64> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                {
                    auto x = dp[i + j], y = dp[i + j + mid];
                    dp[i + j] = (x + y) * inv2 % mod;
                    dp[i + j + mid] = (x - y) * inv2 % mod;
                }
    }
    Main()
    {
        cin >> n >> m >> p;
        vector<vector<int>> e(n, vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            ++e[u - 1][v - 1];
        }
        limit = 1 << n;
        vector<int> popcnt(limit);
        vector<i64> W(limit);
        for (int S = 1; S < limit; ++S)
            popcnt[S] = popcnt[S >> 1] + (S & 1);
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            for (int S = 0; S < (1 << i); ++S)
                W[S | (1 << i)] = W[S] + x;
        }
        vector<vector<i64>> F(n + 1, vector<i64>(limit));
        vector<vector<i64>> G(n + 1, vector<i64>(limit));
        for (int S = 0; S < limit; ++S)
        {
            vector<int> deg(n);
            vector<int> fa(n);
            iota(fa.begin(), fa.end(), 0);
            int c = popcnt[S];
            function<int(int)> find = [&](int x)
            {
                if (x == fa[x])
                    return x;
                return fa[x] = find(fa[x]);
            };
            for (int i = 0; i < n; ++i)
            {
                if (!((S >> i) & 1))
                    continue;
                for (int j = 0; j < n; ++j)
                {
                    if (!((S >> j) & 1))
                        continue;
                    deg[i] += e[i][j];
                    deg[j] += e[i][j];
                    if (e[i][j] && find(i) != find(j))
                    {
                        fa[find(i)] = find(j);
                        --c;
                    }
                }
            }
            bool ok = (c != 1);
            for (int i = 0; i < n; ++i)
                if (deg[i] & 1)
                    ok = true;
            if (ok)
                G[popcnt[S]][S] = quickpow(W[S], p);
        }
        for (int i = 0; i <= n; ++i)
            FWT(G[i]);
        F[0][0] = 1, FWT(F[0]);
        for (int i = 1; i <= n; ++i)
        {
            FWT(F[i]);
            for (int j = 1; j <= i; ++j)
                for (int S = 0; S < (1 << n); ++S)
                    (F[i][S] += F[i - j][S] * G[j][S]) %= mod;
            IFWT(F[i]);
            for (int S = 0; S < (1 << n); ++S)
            {
                if (popcnt[S] == i)
                    (F[i][S] *= quickpow(W[S], mod - 1 - p)) %= mod;
                else
                    F[i][S] = 0;
            }
            if (i < n)
                FWT(F[i]);
        }
        cout << (F[n][limit - 1] + mod) % mod << '\n';
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
