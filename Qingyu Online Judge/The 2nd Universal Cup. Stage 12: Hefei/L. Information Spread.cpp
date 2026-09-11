#include <bits/stdc++.h>
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
    vector<vector<pair<int, int>>> G, H;
    vector<array<int, 21>> fa;
    vector<array<i64, 21>> W;
    vector<int> dfn, low;
    vector<int> dep;
    int dfstime = 0;
    auto dfs(int u, int _fa) -> void
    {
        dfn[u] = ++dfstime;
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 20; ++i)
        {
            fa[u][i + 1] = fa[fa[u][i]][i];
            W[u][i + 1] = W[u][i] * W[fa[u][i]][i] % mod;
        }
        for (auto [v, w] : G[u])
        {
            if (dfn[v])
                continue;
            W[v][0] = w;
            dfs(v, u);
        }
        low[u] = dfstime;
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
    auto query(int u, int v)
    {
        i64 res = 1;
        for (int i = 20; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v])
            {
                (res *= W[u][i]) %= mod;
                u = fa[u][i];
            }
        return res;
    }
    vector<i64> g;
    vector<vector<int>> F;
    auto calc(int u, int _fa) -> i64
    {
        auto f = query(u, _fa);
        i64 res = 1 - g[u];
        for (auto v : F[u])
            (res *= calc(v, u)) %= mod;
        res = (1 - f + res * f) % mod;
        return res;
    }
    auto solve(vector<pair<int, int>> p)
    {
        F.resize(n + 5), g.resize(n + 5);
        ranges::sort(p, {}, [&](auto x)
                     { return dfn[x.first]; });
        vector<int> link;
        for (auto [u, w] : p)
            link.push_back(u);
        for (int i = 1; i < (int)p.size(); ++i)
            link.push_back(lca(p[i - 1].first, p[i].first));
        ranges::sort(link, {}, [&](int u)
                     { return dfn[u]; });
        link.erase(unique(link.begin(), link.end()), link.end());
        for (auto [u, w] : p)
            g[u] = w;
        stack<int> st;
        for (int u : link)
        {
            while (!st.empty() && low[st.top()] < dfn[u])
                st.pop();
            if (!st.empty())
                F[st.top()].push_back(u);
            st.push(u);
        }
        while (st.size() > 1)
            st.pop();
        auto res = calc(st.top(), 1);
        for (int u : link)
        {
            F[u].clear();
            g[u] = 0;
        }
        return (mod + 1 - res) % mod;
    }

    Main()
    {
        cin >> n >> m;
        G.resize(n + 5), H.resize(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v, p, q;
            cin >> u >> v >> p >> q;
            int w = (int)((i64)p * quickpow(q) % mod);
            G[u].emplace_back(v, w);
            H[v].emplace_back(u, w);
        }
        dfn.resize(n + 5), low.resize(n + 5);
        dep.resize(n + 5);
        fa.resize(n + 5), W.resize(n + 5);
        g.resize(n + 5);
        dfs(1, 0);
        cout << 1 << '\n';
        for (int u = 2; u <= n; ++u)
        {
            vector<pair<int, int>> p;
            for (auto [v, w] : H[u])
            {
                if (dfn[u] <= dfn[v] && dfn[v] <= low[u])
                    continue;
                p.emplace_back(v, w);
            }
            cout << solve(p) << '\n';
        }
        F.resize(n + 5);
        G.resize(n + 5);
        H.resize(n + 5);
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