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
struct DominantTree
{
    vector<int> dfn, rk;
    vector<int> fa;
    vector<int> par;
    vector<int> minn;
    vector<int> sdom, idom;
    vector<vector<int>> G, H, U;
    int dfstime;
    auto dfs(int u, int _fa) -> void
    {
        fa[rk[dfn[u] = ++dfstime] = u] = _fa;
        for (auto v : G[u])
        {
            if (dfn[v])
                continue;
            dfs(v, u);
        }
    }
    auto find(int x)
    {
        if (par[x] == x)
            return x;
        find(par[x]);
        if (dfn[sdom[minn[x]]] > dfn[sdom[minn[par[x]]]])
            minn[x] = minn[par[x]];
        return par[x] = par[par[x]];
    }
    DominantTree() = default;
    DominantTree(int n, const vector<pair<int, int>> &edges, int root = 1) : dfstime(0)
    {
        dfn.resize(n + 5), rk.resize(n + 5);
        fa.resize(n + 5), par.resize(n + 5);
        sdom.resize(n + 5), idom.resize(n + 5);
        G.resize(n + 5), H.resize(n + 5), U.resize(n + 5);
        for (auto [x, y] : edges)
        {
            G[x].emplace_back(y);
            H[y].emplace_back(x);
        }
        par.resize(n + 5), minn.resize(n + 5);
        iota(par.begin(), par.end(), 0);
        iota(minn.begin(), minn.end(), 0);
        iota(sdom.begin(), sdom.end(), 0);
        dfs(root, 0);
        for (int i = dfstime; i >= 2; --i)
        {
            int u = rk[i], res = INT_MAX;
            for (auto v : H[u])
            {
                if (!dfn[v])
                    continue;
                find(v);
                if (dfn[v] < dfn[u])
                    res = min(res, dfn[v]);
                else
                    res = min(res, dfn[sdom[minn[v]]]);
            }
            sdom[u] = rk[res];
            par[u] = fa[u];
            U[sdom[u]].emplace_back(u);
            for (auto v : U[u = fa[u]])
            {
                find(v);
                if (u == sdom[minn[v]])
                    idom[v] = u;
                else
                    idom[v] = minn[v];
            }
            U[u].clear();
        }
        for (int i = 2; i <= dfstime; ++i)
        {
            int u = rk[i];
            if (idom[u] != sdom[u])
                idom[u] = idom[idom[u]];
        }
    }
};
struct Main
{
    int n, m;
    vector<pair<int, int>> edges;
    Main()
    {
        cin >> n >> m;
        edges.resize(m);
        for (auto &[x, y] : edges)
            cin >> x >> y;
        DominantTree tree(n, edges);
        vector<int> fuck(n + 5);
        for (int i = tree.dfstime; i >= 2; --i)
        {
            int u = tree.rk[i];
            ++fuck[u];
            fuck[tree.idom[u]] += fuck[u];
        }
        ++fuck[1];
        for (int i = 1; i <= n; ++i)
            cout << fuck[i] << ' ';
        cout << '\n';
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
