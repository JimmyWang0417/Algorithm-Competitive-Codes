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
    int n;
    vector<vector<int>> G;
    vector<int> fa, dep;
    int root = 0;
    int S;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u] = _fa] + 1;
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
        }
        if (dep[u] > dep[root])
            root = u;
    }
    auto solve() -> int
    {
        vector<int> p;
        root = 0;
        dfs(S, 0);
        for (auto i = root; i; i = fa[i])
            p.emplace_back(i);
        if (p.size() == 1)
            return 0;
        ranges::reverse(p);
        vector<bool> vis(n + 5);
        for (auto i : p)
            vis[i] = true;
        // for (auto i : p)
        //     cout << ' ' << i;
        // cout << '\n';
        if (p.size() % 2 == 0)
        {
            vector<vector<int>> H(n + 5);
            vector<int> F(n + 5);
            ranges::iota(F, 0);
            for (int i = 0; i < (int)p.size(); ++i)
                F[p[i]] = p[min(i, (int)p.size() - i - 1)];
            // for (int i = 1; i <= n; ++i)
            //     cout << F[i] << ' ';
            // cout << endl;
            for (int u = 1; u <= n; ++u)
                for (auto v : G[u])
                {
                    if (vis[F[u]] && vis[F[v]])
                        continue;
                    H[F[u]].emplace_back(F[v]);
                }
            for (int i = 0; i + 1 <= ((int)p.size() - 1) / 2; ++i)
            {
                H[p[i]].emplace_back(p[i + 1]);
                H[p[i + 1]].emplace_back(p[i]);
            }
            G.swap(H);
            return 1;
        }
        else
        {
            int r = p[((int)p.size() - 1) / 2];
            vector<vector<int>> H(n + 5);
            vector<int> F(n + 5);
            ranges::iota(F, 0);
            int res = 0;
            for (auto u : G[r])
            {
                if (u == p[((int)p.size() - 1) / 2 - 1])
                    continue;
                root = 0;
                dep[r] = 0;
                dfs(u, r);
                // cout << u << ' ' << r << ' ' << root << '\n';
                if (dep[root] == (int)p.size() / 2)
                {
                    ++res;
                    for (int i = 0, v = root; v != r; v = fa[v], ++i)
                        F[v] = p[i];
                }
            }
            // for (int i = 1; i <= n; ++i)
            //     cout << F[i] << ' ';
            // cout << endl;
            for (int u = 1; u <= n; ++u)
                for (auto v : G[u])
                {
                    if (vis[F[u]] && vis[F[v]])
                        continue;
                    H[F[u]].emplace_back(F[v]);
                }
            for (int i = 0; i + 1 <= ((int)p.size() - 1) / 2; ++i)
            {
                H[p[i]].emplace_back(p[i + 1]);
                H[p[i + 1]].emplace_back(p[i]);
            }
            G.swap(H);
            return res;
        }
    }
    Main()
    {
        cin >> n;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            G[x].emplace_back(y);
            G[y].emplace_back(x);
        }
        fa.resize(n + 5), dep.resize(n + 5);
        dfs(1, 0);
        S = root;
        int res = 0;
        while (true)
        {
            // for (int u = 1; u <= n; ++u)
            //     for (auto v : G[u])
            //         if (u < v)
            //             cout << u << ' ' << v << '\n';
            // cout << endl;
            int v = solve();
            if (v)
                res += v;
            else
                break;
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