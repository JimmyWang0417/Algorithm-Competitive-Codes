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
    vector<vector<int>> G;
    vector<vector<int>> bel, fa, par, dist;
    vector<int> sze, maxsze;
    vector<bool> vis;
    int root, sum;
    auto getroot(int u, int _fa) -> void
    {
        sze[u] = 1;
        maxsze[u] = 0;
        for (auto v : G[u])
        {
            if (v == _fa || vis[v])
                continue;
            getroot(v, u);
            sze[u] += sze[v];
            maxsze[u] = max(maxsze[u], sze[v]);
        }
        maxsze[u] = max(maxsze[u], sum - sze[u]);
        if (maxsze[u] < maxsze[root])
            root = u;
    }
    auto dfs(int u, int _fa, int d, int be) -> void
    {
        fa[u].emplace_back(root);
        par[u].emplace_back(_fa);
        dist[u].emplace_back(d);
        bel[u].emplace_back(be);
        for (auto v : G[u])
        {
            if (v == _fa || vis[v])
                continue;
            dfs(v, u, d + 1, !be ? v : be);
        }
    }
    auto solve(int u) -> void
    {
        getroot(u, 0);
        u = root;
        dfs(u, 0, 0, 0);
        vis[u] = true;
        for (auto v : G[u])
        {
            if (vis[v])
                continue;
            maxsze[root = 0] = sum = sze[v];
            solve(v);
        }
    }
    vector<int> a;
    vector<array<multiset<pair<int, int>>, 2>> f, g;
    auto find(int u, int v, int c)
    {
        auto it = g[u][c].lower_bound({v, 0});
        if (it == g[u][c].end() || it->first != v)
            return -1;
        return it->second;
    }
    auto add(int u, int v, int c)
    {
        int res = find(u, v, c);
        if (res == -1)
            return;
        f[u][c].emplace(res, v);
    }
    auto del(int u, int v, int c)
    {
        int res = find(u, v, c);
        if (res == -1)
            return;
        f[u][c].erase(f[u][c].find({res, v}));
    }
    auto add(int u, int c)
    {
        for (int i = 0; i < (int)fa[u].size(); ++i)
        {
            del(fa[u][i], bel[u][i], c);
            g[fa[u][i]][c].emplace(bel[u][i], dist[u][i]);
            add(fa[u][i], bel[u][i], c);
        }
    }
    auto del(int u, int c)
    {
        for (int i = 0; i < (int)fa[u].size(); ++i)
        {
            del(fa[u][i], bel[u][i], c);
            g[fa[u][i]][c].erase(g[fa[u][i]][c].find({bel[u][i], dist[u][i]}));
            add(fa[u][i], bel[u][i], c);
        }
    }
    auto query(int u)
    {
        pair<int, int> minn[2] = {{INT_MAX / 2, 0}, {INT_MAX / 2, 0}},
                       rmin[2] = {{INT_MAX / 2, 0}, {INT_MAX / 2, 0}};
        for (int c = 0; c < 2; ++c)
        {
            if (!f[u][c].empty())
                minn[c] = *f[u][c].begin();
            if (f[u][c].size() >= 2)
                rmin[c] = *next(f[u][c].begin());
        }
        for (int i = 0; i + 1 < (int)fa[u].size(); ++i)
        {
            for (int c = 0; c < 2; ++c)
            {
                auto res = INT_MAX / 2;
                if (!f[fa[u][i]][c].empty() && f[fa[u][i]][c].begin()->second != bel[u][i])
                    res = min(res, f[fa[u][i]][c].begin()->first + dist[u][i]);
                else if (f[fa[u][i]][c].size() >= 2)
                    res = min(res, next(f[fa[u][i]][c].begin())->first + dist[u][i]);
                pair<int, int> now = make_pair(res, par[u][i]);
                if (now < minn[c])
                    swap(now, minn[c]);
                if (now < rmin[c] && now.second != minn[c].second)
                    rmin[c] = now;
            }
        }

        int res = INT_MAX;
        if (minn[0].second == minn[1].second)
            res = min(minn[0].first + rmin[1].first, rmin[0].first + minn[1].first);
        else
            res = minn[0].first + minn[1].first;
        return res <= n - 1 ? res : -1;
    }
    Main()
    {
        cin >> n >> m;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        a.resize(n + 5);
        {
            string s;
            cin >> s;
            for (int i = 1; i <= n; ++i)
                a[i] = s[i - 1] == 'R' ? 0 : (s[i - 1] == 'G' ? 1 : 2);
        }
        bel.resize(n + 5), fa.resize(n + 5);
        par.resize(n + 5), dist.resize(n + 5);
        sze.resize(n + 5), maxsze.resize(n + 5);
        vis.resize(n + 5);

        maxsze[root = 0] = sum = n;
        solve(1);
        // for (int i = 1; i <= n; ++i)
        // {
        //     cout << i << ": ";
        //     for (auto j : fa[i])
        //         cout << j << ' ';
        //     cout << '\n';
        // }
        f.resize(n + 5), g.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            if (a[i] <= 1)
                add(i, a[i]);
        // for (auto [u, v] : f[4][0])
        //     cout << "(" << u << ", " << v << ") ";
        // cout << '\n';
        for (int i = 0; i < m; ++i)
        {
            int o, v;
            char c;
            cin >> o >> v;
            if (o == 1)
            {
                cin >> c;
                if (a[v] <= 1)
                    del(v, a[v]);
                a[v] = c == 'R' ? 0 : (c == 'G' ? 1 : 2);
                if (a[v] <= 1)
                    add(v, a[v]);
            }
            else
                cout << query(v) << '\n';
        }
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
