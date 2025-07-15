#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
int n, m;
vector<int> G[N];
vector<ll> pre[N], suf[N];
ll f[N], g[N];
inline void dfs(int u)
{
    f[u] = 1;
    for (auto v : G[u])
    {
        dfs(v);
        (f[u] *= f[v] + 1) %= mod;
    }
    if (G[u].empty())
        return;
    pre[u].resize(G[u].size()), suf[u].resize(G[u].size());
    pre[u].front() = suf[u].back() = 1;
    for (int i = 0; i < (int)pre[u].size() - 1; ++i)
        pre[u][i + 1] = pre[u][i] * (f[G[u][i]] + 1) % mod;
    for (int i = (int)suf[u].size() - 1; i >= 1; --i)
        suf[u][i - 1] = suf[u][i] * (f[G[u][i]] + 1) % mod;
}
inline void dfs(int u, ll las)
{
    g[u] = f[u] * (las + 1);
    for (int i = 0; i < (int)G[u].size(); ++i)
    {
        int v = G[u][i];
        dfs(v, pre[u][i] * suf[u][i] % mod * (las + 1) % mod);
    }
}
int sze[N], son[N], dep[N], fa[N], top[N];
int dfn[N], rk[N], dfstime;
inline void dfs1(int u, int _fa)
{
    sze[u] = 1;
    dep[u] = dep[fa[u] = _fa] + 1;
    for (int v : G[u])
    {
        dfs1(v, u);
        sze[u] += sze[v];
        if (sze[v] > sze[son[u]])
            son[u] = v;
    }
}
inline void dfs2(int u, int topf)
{
    top[u] = topf;
    rk[dfn[u] = ++dfstime] = u;
    if (son[u])
        dfs2(son[u], topf);
    for (int v : G[u])
    {
        if (dfn[v])
            continue;
        dfs2(v, v);
    }
}
auto lowbit = [](int x)
{
    return x & (-x);
};
ll c[N];
inline void update(int pos, ll val)
{
    for (int i = pos; i <= n; i += lowbit(i))
        (c[i] += val) %= mod;
}
inline ll query(int pos)
{
    ll res = 0;
    for (int i = pos; i; i -= lowbit(i))
        (res += c[i]) %= mod;
    return res;
}
inline ll query(int l, int r)
{
    return (query(r) - query(l - 1) + mod) % mod;
}
inline ll querytree(int x, int y)
{
    ll res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        res += query(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    (res += query(dfn[x] + 1, dfn[y]) + g[x]) %= mod;
    return res;
}
inline void clear()
{
    for (int i = 1; i <= n; ++i)
    {
        G[i].clear();
        dfn[i] = rk[i] = 0;
        top[i] = dep[i] = fa[i] = 0;
        sze[i] = son[i] = 0;
        c[i] = 0;
        pre[i].clear(), suf[i].clear();
        f[i] = g[i] = 0;
    }
    dfstime = 0;
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 2; i <= n; ++i)
    {
        int p;
        cin >> p;
        G[p].push_back(i);
    }
    dfs(1);
    dfs(1, 0);
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        update(dfn[i], f[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        cout << querytree(u, v) << '\n';
    }
    clear();
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}