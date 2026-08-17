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
template <typename T>
auto eval(const vector<T> &Y, int k) // a0, a1, ... am-1
{
    int n = (int)Y.size() - 1;
    vector<i64> fac(n + 1), ifac(n + 1);
    vector<i64> pre(n + 1), suf(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
    pre[0] = 1;
    for (int i = 0; i < n; ++i)
        pre[i + 1] = pre[i] * (k - i) % mod;
    suf[n] = 1;
    for (int i = n; i >= 1; --i)
        suf[i - 1] = suf[i] * (k - i) % mod;
    i64 res = 0;
    for (int i = 0; i <= n; ++i)
        (res += ((n - i) & 1 ? -1 : 1) * Y[i] *
                (pre[i] * suf[i] % mod) % mod *
                (ifac[i] * ifac[n - i] % mod)) %= mod;
    return res;
}
struct Main
{
    int n, k;
    vector<vector<int>> G;
    vector<vector<i64>> dp;
    auto dfs(int u, int _fa) -> void
    {
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            i64 pre = 0;
            for (int i = 0; i <= n; ++i)
            {
                (pre += dp[v][i]) %= mod;
                (dp[u][i] *= pre) %= mod;
            }
        }
    }
    Main()
    {
        cin >> n >> k;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dp.resize(n + 1, vector<i64>(n + 1, 1));
        dfs(1, 0);
        cout << (eval(dp[1], k) + mod) % mod << '\n';
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
