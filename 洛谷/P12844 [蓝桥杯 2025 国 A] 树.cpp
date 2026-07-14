#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct Main
{
    int n;
    vector<vector<int>> g;
    vector<array<i64, 3>> dp;
    auto dfs(int u, int _fa) -> void
    {
        dp[u][0] = 1;
        dp[u][2] = 1;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            dp[u] = {
                (dp[u][0] * dp[v][2]) % mod,
                (dp[u][1] * (dp[v][1] + dp[v][2]) % mod + dp[u][2] * dp[v][0] % mod) % mod,
                (dp[u][2] * (dp[v][1] + dp[v][2]) % mod)
            };
        }
    }
    Main()
    {
        cin >> n;
        dp.resize(n + 5);
        g.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs(1, 0);
        // for (int i = 1; i <= n; ++i)
        //     cout << dp[i][0] << ' ' << dp[i][1] << ' ' << dp[i][2] << '\n';
        cout << (dp[1][0] + dp[1][1] + dp[1][2] + mod - 1) % mod << '\n';
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