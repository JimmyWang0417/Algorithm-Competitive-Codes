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
constexpr int inv2 = quickpow(2);
constexpr auto lowbit = [](int x)
{ return x & (-x); };
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
    vector<int> in, out;
    vector<int> popcnt;
    vector<int> A, B;
    vector<int> Log;
    vector<int> power;
    vector<vector<i64>> f;
    Main()
    {
        cin >> n >> m;
        limit = 1 << n;
        in.resize(n), out.resize(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            out[u - 1] |= 1 << (v - 1);
            in[v - 1] |= 1 << (u - 1);
        }
        Log.resize(limit);
        for (int i = 0; i < n; ++i)
            Log[1 << i] = i;
        popcnt.resize(limit);
        for (int i = 1; i < limit; ++i)
            popcnt[i] = popcnt[i >> 1] + (i & 1);

        power.resize(n * (n - 1) + 5);
        power[0] = 1;
        for (int i = 1; i <= n * (n - 1); ++i)
            power[i] = power[i - 1] * 2 % mod;

        A.resize(limit), B.resize(limit);
        f.resize(limit, vector<i64>(n + 1));
        for (int S = 1; S < limit; ++S)
        {
            int x = lowbit(S);
            A[S] = A[S ^ x] + popcnt[in[Log[x]] & (S ^ x)] + popcnt[out[Log[x]] & S];
        }
        for (int S = 0; S < limit; ++S)
        {
            B[S] = 0;
            for (int T = (S - 1) & S; T; T = (T - 1) & S)
            {
                int x = lowbit(S - T);
                B[T] = B[T | x] + popcnt[out[Log[x]] & (T | x)] - popcnt[(S - T) & in[Log[x]]];
            }
            f[S][popcnt[S]] = power[A[S]];
            for (int T = (S - 1) & S; T; T = (T - 1) & S)
                (f[S][popcnt[S]] -= power[A[S ^ T] + B[T]] * f[T][popcnt[T]]) %= mod;
        }
        FWT(f);
        vector<i64> inv(n + 5);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;
        for (int S = 0; S < limit; ++S)
        {
            vector<i64> g(n + 1);
            for (int i = 1; i <= n; ++i)
            {
                i64 res = 0;
                for (int j = 0; j < i; ++j)
                    (res += j * g[j] % mod * (-f[S][i - j])) %= mod;
                g[i] = (-f[S][i] - inv[i] * res) % mod;
            }
            for (int i = 0; i <= n; ++i)
                f[S][i] = -g[i];
        }
        IFWT(f);
        cout << (f[limit - 1][n] + mod) % mod << '\n';
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