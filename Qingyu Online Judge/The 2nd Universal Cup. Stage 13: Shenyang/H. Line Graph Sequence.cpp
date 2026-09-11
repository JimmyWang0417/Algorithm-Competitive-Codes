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
constexpr int mod = 1e9 + 7;
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
    int n, m, q;
    int limit;
    vector<vector<int>> G;
    vector<bool> vis;
    vector<int> p;
    auto dfs(int u) -> void
    {
        p.emplace_back(u);
        vis[u] = true;
        for (auto v : G[u])
        {
            if (vis[v])
                continue;
            dfs(v);
        }
    }
    auto nxtedges()
    {
        i64 res = 0;
        n = (int)G.size() - 5;
        for (int u = 1; u <= n; ++u)
            res += (i64)G[u].size() * (G[u].size() - 1) / 2;
        return res;
    }
    auto nxt()
    {
        unordered_map<i64, int> mp;
        n = (int)G.size() - 5;
        int cnt = 0;
        for (int u = 1; u <= n; ++u)
            for (auto v : G[u])
                if (u < v)
                    mp[(i64)u * n + v] = mp[(i64)v * n + u] = ++cnt;
        vector<vector<int>> H(cnt + 5);
        for (int u = 1; u <= n; ++u)
        {
            for (auto v : G[u])
                for (auto w : G[u])
                {
                    if (v == w)
                        continue;
                    H[mp[(i64)u * n + v]].emplace_back(mp[(i64)u * n + w]);
                }
        }
        return H;
    }
    Main()
    {
        cin >> n >> m >> q;
        G.resize(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        limit = max(n, m) * 10;
        vis.resize(n + 5);
        int c1 = 0;
        vector<int> suf(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            if (vis[i])
                continue;
            dfs(i);
            bool flag = true;
            for (int u : p)
                flag &= (G[u].size() <= 2);
            if (flag)
            {
                bool minus = false;
                for (int u : p)
                    if (G[u].size() <= 1)
                    {
                        minus = true;
                        break;
                    }
                if (minus)
                    suf[p.size()]++;
            }
            else
            {
                int v = 0;
                for (auto u : p)
                    if (G[v].size() < G[u].size())
                        v = u;
                if (v && p.size() == 4 && G[v].size() == 3)
                {
                    flag = true;
                    for (auto u : p)
                    {
                        if (u == v)
                            continue;
                        flag &= (G[u].size() == 1);
                    }
                    if (!flag)
                        ++c1;
                    else
                        ++suf[1];
                }
                else
                    ++c1;
            }
            p.clear();
        }
        int res = n;
        if (c1 == 0)
        {
            for (int i = n - 1; i >= 1; --i)
                suf[i] += suf[i + 1];
            for (int i = 1; i < q && i <= n; ++i)
                res -= suf[i];
        }
        else
        {
            if (q > 1)
                res = min(n, m);
            for (int i = 2; i < q && i <= 300; ++i)
            {
                auto now = nxtedges();
                if (now > limit)
                    break;
                res = min(res, (int)now);
                G = nxt();
                // cout << i << ' ' << G.size() - 5 << ": \n";
                // for (int u = 1; u <= (int)G.size() - 5; ++u)
                // {
                //     for (auto v : G[u])
                //         if (u < v)
                //             cout << u << ' ' << v << '\n';
                // }
            }
        }
        cout << res << '\n';
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