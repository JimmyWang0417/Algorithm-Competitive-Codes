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
struct Main
{
    int n, m;
    vector<vector<int>> G;
    vector<int> fa;
    vector<int> f, sumf, g, sumg;
    vector<bool> vis;
    auto down(int u, int _fa, int len, int cur) -> void
    {
        int x = cur ^ sumf[u];
        if (x <= n)
            vis[x] = true;

        if (len > 1)
            for (auto v : G[u])
            {
                if (v == _fa)
                    continue;
                down(v, u, len - 1, cur ^ sumf[u] ^ f[v]);
            }
    }
    auto dfs1(int u, int _fa) -> void
    {
        fa[u] = _fa;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs1(v, u);
            sumf[u] ^= f[v];
        }
        down(u, _fa, m, 0);
        while (vis[f[u]])
            ++f[u];
        vis.assign(n + 5, 0);
    }
    auto up(int u, int _fa, int len, int cur) -> void
    {
        int x = cur ^ sumg[u] ^ f[_fa];
        if (x <= n)
            vis[x] = true;
        if (len > 1)
        {
            for (auto v : G[u])
            {
                if (v == _fa || v == fa[u])
                    continue;
                down(v, u, len - 1, cur ^ sumg[u] ^ f[_fa] ^ f[v]);
            }
            if (fa[u])
                up(fa[u], u, len - 1, cur ^ sumf[u] ^ f[_fa]);
        }
    }
    auto dfs2(int u, int _fa) -> void
    {
        if (_fa)
        {
            up(_fa, u, m, 0);
            int other = 0;
            while (vis[other])
                ++other;
            sumg[u] ^= other;
            vis.assign(n + 5, false);
        }
        for (int v : G[u])
        {
            if (v == _fa)
                continue;
            dfs2(v, u);
        }
    }
    Main()
    {
        cin >> n >> m;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        fa.resize(n + 5);
        f.resize(n + 5);
        sumf.resize(n + 5);
        vis.resize(n + 5);
        dfs1(1, 0);
        sumg = sumf;
        dfs2(1, 0);
        for (int i = 1; i <= n; ++i)
            cout << !!sumg[i];
        cout << '\n';
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
