#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, m;
int fa[N], where[N];
vector<pair<int, int>> G[N];
struct unionSet
{
    vector<int> fa;
    unionSet(int _n = 0)
    {
        fa.resize(_n + 5);
        iota(fa.begin(), fa.end(), 0);
    }
    inline int find(int x)
    {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline bool merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return false;
        fa[x] = y;
        return true;
    }
};
auto _main()
{
    cin >> n >> m;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }
    vector<ll> f(m + 5), g(m + 5);
    vector<vector<ll>> dp(n + 5, vector<ll>(m + 5));
    ll ans = 0;
    function<void(int)> dfs = [&](int u)
    {
        dp[u][0] = 1;
        for (auto [v, id] : G[u])
        {
            if (v == fa[u])
                continue;
            fa[v] = u;
            where[id] = v;
            dfs(v);
            for (int i = 0; i < m; ++i)
                ans += dp[u][i] * dp[v][m - i - 1];
            for (int i = 0; i < m; ++i)
                dp[u][i + 1] += dp[v][i];
        }
    };
    dfs(1);
    unionSet se(n);
    for (int i = 1; i < n; ++i)
    {
        int x;
        cin >> x;
        x = (int)((x + ans) % (n - 1) + 1);
        int v = se.find(where[x]), u = se.find(fa[where[x]]);
        // cout << v << ' ' << u << '\n';
        for (int j = 0; j <= m && u; ++j, u = se.find(fa[v = u]))
        {
            for (int k = 0; k < m; ++k)
                ans -= (dp[u][k] - (k > 0 ? dp[v][k - 1] : 0)) * dp[v][m - 1 - k];
            // cout << ' ' << ans << '\n';
        }

        v = se.find(where[x]), u = se.find(fa[where[x]]);

        f = dp[v];
        for (int j = 0; j <= m && u; ++j, u = se.find(fa[v = u]))
        {
            g = dp[u];
            for (int k = 0; k < m; ++k)
                dp[u][k + 1] -= f[k];
            swap(f, g);
        }

        v = se.find(where[x]), u = se.find(fa[where[x]]);

        // cout << u << ' ' << v << ' ' << dp[v][2] << '\n';
        for (int k = 0; k <= m; ++k)
            ans += dp[u][k] * dp[v][m - k];
        for (int k = 0; k <= m; ++k)
            dp[u][k] += dp[v][k];

        u = se.find(fa[v = u]);
        for (int j = 1; j <= m && u; ++j, u = se.find(fa[v = u]))
        {
            for (int k = 0; k < m; ++k)
                ans += dp[u][k] * dp[v][m - 1 - k];
            for (int k = 0; k < m; ++k)
                dp[u][k + 1] += dp[v][k];
        }
        se.merge(where[x], fa[where[x]]);
        cout << ans << '\n';
    }
}
auto _clear()
{
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
    {
        _main();
        _clear();
    }
    return 0;
}