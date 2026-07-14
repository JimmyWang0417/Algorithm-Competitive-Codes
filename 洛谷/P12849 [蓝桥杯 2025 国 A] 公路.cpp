#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct Main
{
    int n;
    vector<vector<pair<int, int>>> g;
    vector<vector<int>> h;
    vector<vector<int>> a;
    vector<array<int, 23>> fa;
    vector<int> dep, dfn, sze;
    vector<bool> b;
    int dfstime;
    auto init(int u, int _fa) -> void
    {
        sze[u] = 1;
        dfn[u] = ++dfstime;
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 20; ++i)
            fa[u][i + 1] = fa[fa[u][i]][i];
        for (auto [v, w] : g[u])
        {
            if (v == _fa)
                continue;
            init(v, u);
            sze[u] += sze[v];
            a[w].emplace_back(v);
        }
    }
    auto LCA(int u, int v)
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
    auto jump(int u, int d)
    {
        for (int i = 20; i >= 0; --i)
            if ((d >> i) & 1)
                u = fa[u][i];
        return u;
    }
    i64 total;
    auto dfs(int u) -> int
    {
        int remove = 0;
        for (int v : h[u])
        {
            remove += dfs(v);
        }
        if (b[u])
        {
            total -= (i64)(sze[u] - remove) * (sze[u] - remove - 1);
            remove = sze[u];
        }
        return remove;
    }
    Main() : dfstime(0)
    {
        cin >> n;
        g.resize(n + 5);
        h.resize(n + 5);
        a.resize(n + 5);
        b.resize(n + 5);
        fa.resize(n + 5);
        dep.resize(n + 5);
        dfn.resize(n + 5);
        sze.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        init(1, 0);
        vector<int> st(n + 5);
        i64 res = 0;
        for (int c = 1; c <= n; ++c)
        {
            if (a[c].empty())
                continue;
            int top = 0;
            sort(a[c].begin(), a[c].end(), [&](int x, int y)
                 { return dfn[x] < dfn[y]; });
            vector<int> p;
            for (int u : a[c])
            {
                b[u] = true;
                p.push_back(u);
                if (!top)
                    st[++top] = u;
                else
                {
                    int lca = LCA(st[top], u);
                    while (top > 1 && dfn[lca] <= dfn[st[top - 1]])
                    {
                        h[st[top - 1]].push_back(st[top]);
                        --top;
                    }
                    if (lca != st[top])
                    {
                        h[lca].push_back(st[top]);
                        st[top] = lca;
                        p.push_back(lca);
                    }
                    st[++top] = u;
                }
            }
            while (top > 1)
            {
                h[st[top - 1]].push_back(st[top]);
                top--;
            }
            total = (i64)n * (n - 1);
            {
                auto remove = dfs(st[top]);
                total -= (i64)(n - remove) * (n - remove - 1);
            }
            res += total;
            for (int i : p)
            {
                h[i].clear();
                b[i] = 0;
            }
        }
        cout << res << '\n';
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}