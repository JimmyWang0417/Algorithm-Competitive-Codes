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
constexpr int N = 19;
struct Main
{
    int n, m;
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
    auto FWT(vector<array<T, N>> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        (dp[i + j + mid][k] += dp[i + j][k]) %= mod;
    }
    template <typename T>
    auto IFWT(vector<array<T, N>> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    for (int k = 0; k <= n; ++k)
                        (dp[i + j + mid][k] -= dp[i + j][k]) %= mod;
    }
    vector<int> power, popcnt;
    Main()
    {
        cin >> n >> m;
        limit = 1 << n;

        vector<i64> inv(n + 5);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;

        power.resize(n * (n - 1) / 2 + 5);
        power[0] = 1;
        for (int i = 1; i <= n * (n - 1) / 2; ++i)
            power[i] = power[i - 1] * i;
        popcnt.resize(limit);
        for (int S = 1; S < limit; ++S)
            popcnt[S] = popcnt[S >> 1] + (S & 1);

        vector<i64> a(limit);
        vector<vector<i64>> e(n, vector<i64>(limit));
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            ++a[(1 << u) | (1 << v)];
            ++e[u][1 << v], ++e[v][1 << u];
        }
        FWT(a);
        for (int i = 0; i < n; ++i)
            FWT(e[i]);

        vector<i64> F(limit);
        for (int i = 0; i < limit; ++i)
            F[i] = quickpow(2, a[i]);
        auto ln = [&](auto arr)
        {
            vector<array<i64, N>> f(limit);
            for (int S = 0; S < limit; ++S)
                f[S][popcnt[S]] = arr[S];
            FWT(f);
            for (int S = 0; S < limit; ++S)
            {
                array<i64, N> g{};
                for (int i = 1; i <= n; ++i)
                {
                    i64 res = 0;
                    for (int j = 0; j < i; ++j)
                        (res += j * g[j] % mod * f[S][i - j]) %= mod;
                    g[i] = (f[S][i] - inv[i] * res) % mod;
                }
                f[S] = g;
            }
            IFWT(f);
            for (int S = 0; S < limit; ++S)
                arr[S] = f[S][popcnt[S]];
            return arr;
        };
        auto calc = [&](auto A, const auto &B)
        {
            static vector<array<i64, N>> f(limit);
            static vector<array<i64, N>> g(limit);
            for (int S = 0; S < limit; ++S)
            {
                f[S].fill(0), g[S].fill(0);
                f[S][popcnt[S]] = A[S];
                g[S][popcnt[S]] = B[S];
            }
            FWT(f), FWT(g);
            for (int S = 0; S < limit; ++S)
            {
                {
                    array<i64, N> h{};
                    h[0] = 1;
                    for (int i = 1; i <= n; ++i)
                    {
                        i64 res = 0;
                        for (int j = 1; j <= i; ++j)
                            (res += j * f[S][j] % mod * h[i - j]) %= mod;
                        h[i] = res * inv[i] % mod;
                    }
                    f[S] = h;
                }
                {
                    array<i64, N> h{};
                    for (int i = 0; i <= n; ++i)
                        for (int j = 0; j <= i; ++j)
                            (h[i] += f[S][j] % mod * g[S][i - j]) %= mod;
                    f[S] = h;
                }
            }
            IFWT(f);
            for (int S = 0; S < limit; ++S)
                A[S] = f[S][popcnt[S]];
            return A;
        };
        auto G = ln(F);
        for (int i = n - 1; i >= 1; --i)
        {
            vector<i64> H(limit);
            for (int S = 0; S < limit; ++S)
            {
                if ((S >> i) & 1)
                    continue;
                H[S] = -G[S] * e[i][S & ((1 << i) - 1)] % mod;
            }
            H = calc(H, G);
            for (int S = 0; S < limit; ++S)
                if ((S >> i) & 1)
                    G[S] = H[S];
        }
        cout << (G[limit - 1] + mod) % mod << '\n';
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