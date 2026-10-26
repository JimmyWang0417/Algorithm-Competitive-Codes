#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
struct Main
{
    int n, m;
    vector<array<vector<i64>, 4>> dp;
    vector<vector<pair<int, int>>> G;
    vector<int> sze;
    auto dfs(int u, int _fa, int au) -> void
    {
        dp[u][0][0] = 0;
        dp[u][1][0] = 0;
        dp[u][2][0] = 0;
        sze[u] = 1;
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u, w);
            array<vector<i64>, 4> f = {
                vector<i64>(m + 1, LLONG_MIN / 2),
                vector<i64>(m + 1, LLONG_MIN / 2),
                vector<i64>(m + 1, LLONG_MIN / 2),
                vector<i64>(m + 1, LLONG_MIN / 2)};
            for (int i = 0; i <= sze[u] && i <= m; ++i)
                for (int j = 0; j <= sze[v] && i + j <= m; ++j)
                {
                    f[0][i + j] = max({f[0][i + j],
                                       dp[u][0][i] + max(dp[v][2][j], dp[v][3][j]),
                                       dp[u][2][i] + dp[v][0][j] + w});
                    f[1][i + j] = max({f[1][i + j],
                                       dp[u][1][i] + max(dp[v][2][j], dp[v][3][j]),
                                       dp[u][2][i] + dp[v][1][j],
                                       dp[u][0][i] + dp[v][0][j] + w});
                    f[2][i + j] = max(f[2][i + j], dp[u][2][i] + max(dp[v][2][j], dp[v][3][j]));
                }
            dp[u] = f;
            sze[u] += sze[v];
        }
        dp[u][3][0] = 0;
        for (int i = 0; i + 1 <= m && i + 1 <= sze[u]; ++i)
            dp[u][3][i + 1] = dp[u][1][i] + au;
    }
    Main()
    {
        cin >> n >> m;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            G[u].emplace_back(v, w);
            G[v].emplace_back(u, w);
        }
        ++m;
        dp.resize(n + 1, {vector<i64>(m + 1, LLONG_MIN / 2),
                          vector<i64>(m + 1, LLONG_MIN / 2),
                          vector<i64>(m + 1, LLONG_MIN / 2),
                          vector<i64>(m + 1, LLONG_MIN / 2)});
        sze.resize(n + 5);
        dfs(1, 0, 0);
        auto res = dp[1][3][0];
        for (int i = 1; i <= m; ++i)
            cout << (res = max(res, dp[1][3][i])) << ' ';
        cout << '\n';
        // for (int u = 1; u <= n; ++u)
        // {
        //     cout << dp[u][3].size() << '\n';
        //     // for (int i = 0; i <= m; ++i)
        //     //     cout << dp[u][3][i] << ' ';
        //     // cout << '\n';
        // }
        // cout << dp[3][3][1] << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}
