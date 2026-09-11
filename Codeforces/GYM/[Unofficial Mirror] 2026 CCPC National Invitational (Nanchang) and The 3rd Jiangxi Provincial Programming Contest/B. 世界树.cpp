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
    int n, m;
    vector<vector<pair<int, int>>> G;
    vector<i64> dis, maxdis, other;
    vector<array<int, 21>> fa;
    vector<array<i64, 21>> dp;
    vector<int> dep;
    vector<array<pair<i64, int>, 3>> maxd;
    auto init(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u][0] = _fa] + 1;
        maxdis[u] = dis[u];
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            dis[v] = dis[u] + w;
            init(v, u);
            maxdis[u] = max(maxdis[u], maxdis[v]);
        }
    }
    auto dfs(int u, int _fa) -> void
    {
        maxd[u][0] = {dis[u], u}, maxd[u][1] = maxd[u][2] = {LLONG_MIN, 0};
        for (int i = 0; i < 20; ++i)
            dp[u][i + 1] = max(dp[u][i], dp[fa[u][i]][i]);
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            pair<i64, int> now = {maxdis[v], v};
            for (int i = 0; i < 3; ++i)
            {
                if (now > maxd[u][i])
                    swap(now, maxd[u][i]);
            }
        }
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            if (maxd[u][0].second != v)
                dp[v][0] = maxd[u][0].first - dis[u];
            else
                dp[v][0] = maxd[u][1].first - dis[u];
            other[v] = max(dp[v][0], other[u]) + w;
            dfs(v, u);
        }
    }
    auto lca(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        for (int i = 20; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v])
                u = fa[u][i];
        if (u == v)
            return u;
        for (int i = 20; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                u = fa[u][i];
                v = fa[v][i];
            }
        return fa[u][0];
    }
    auto jump(int u, int k)
    {
        for (int i = 20; i >= 0; --i)
            if ((k >> i) & 1)
                u = fa[u][i];
        return u;
    }
    auto query(int u, int v)
    {
        if (dep[u] > dep[v])
            swap(u, v);
        int w = lca(u, v);
        i64 len = dis[u] + dis[v] - dis[w] * 2, res = 0;
        if (u == w)
        {
            res = max(res, maxdis[v] - dis[v]);
            for (int i = 20; i >= 0; --i)
                if (dep[fa[v][i]] >= dep[w])
                {
                    res = max(res, dp[v][i]);
                    v = fa[v][i];
                }
            res = max({res, other[u]});
        }
        else
        {
            res = max({res, maxdis[u] - dis[u], maxdis[v] - dis[v]});
            if (dep[u] < dep[v])
                swap(u, v);
            for (int i = 20; i >= 0; --i)
                if (dep[fa[u][i]] >= dep[v])
                {
                    res = max(res, dp[u][i]);
                    u = fa[u][i];
                }
            for (int i = 20; i >= 0; --i)
                if (fa[u][i] != fa[v][i])
                {
                    res = max({res, dp[u][i], dp[v][i]});
                    u = fa[u][i], v = fa[v][i];
                }
            res = max(res, other[w]);
            for (int i = 0; i < 3; ++i)
            {
                if (maxd[w][i].second == u || maxd[w][i].second == v)
                    continue;
                res = max(res, maxd[w][i].first - dis[w]);
                break;
            }
        }
        return len + res * 2;
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
        dis.resize(n + 5), maxdis.resize(n + 5);
        fa.resize(n + 5), dp.resize(n + 5);
        maxd.resize(n + 5), dep.resize(n + 5);
        other.resize(n + 5);
        init(1, 0);
        dfs(1, 0);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            cout << query(u, v) << '\n';
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