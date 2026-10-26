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
    constexpr static auto inv2 = quickpow(2);
    constexpr static auto inv4 = quickpow(4);
    int n;
    vector<vector<int>> G;
    vector<array<i64, 4>> dp; // L, R, LR, D
    auto dfs(int u) -> i64
    {
        if (G[u].empty())
        {
            dp[u] = {1, 1, 1, 0};
            return 0;
        }
        i64 res = 0;
        for (auto v : G[u])
        {
            (res += dfs(v)) %= mod;
            if (v == G[u].front())
            {
                dp[u][0] = inv2 * dp[v][0] % mod;
                dp[u][1] = inv2 * dp[v][1] % mod;
                dp[u][2] = dp[v][2];
                dp[u][3] = inv2 * (dp[v][2] + dp[v][3]) % mod;
            }
            else
            {
                (res += inv2 * (1 - inv2 * dp[u][1] % mod * dp[v][0] % mod)) %= mod;
                array<i64, 4> nxtdp;
                nxtdp[0] = (dp[u][0] + inv4 * dp[u][3] % mod * dp[v][0] % mod) % mod;
                nxtdp[1] = (inv2 * dp[v][1] % mod +
                            inv4 * dp[u][1] % mod * (dp[v][2] + dp[v][3]) % mod) %
                           mod;
                nxtdp[2] = (inv2 * dp[u][0] % mod * dp[v][1] % mod +
                            inv2 * dp[u][2] % mod * dp[v][2] % mod -
                            inv4 * (dp[u][2] - dp[u][3]) % mod * (dp[v][2] - dp[v][3]) % mod) %
                           mod;
                nxtdp[3] = inv4 * dp[u][3] % mod * (dp[v][2] + dp[v][3]) % mod;
                dp[u].swap(nxtdp);
            }
        }
        return res;
    }
    Main()
    {
        cin >> n;
        G.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            int c;
            cin >> c;
            G[i].resize(c);
            for (auto &j : G[i])
                cin >> j;
        }
        dp.resize(n + 5);
        i64 res =((n + 1) * inv2 % mod - dfs(1)) % mod;
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
