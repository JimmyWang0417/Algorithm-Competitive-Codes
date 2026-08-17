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
    int n, m, S, T;
    map<pair<int, int>, int> mp;
    vector<vector<int>> g;
    vector<int> dep, fa;
    vector<pair<int, int>> edges;
    vector<bool> vis;
    auto solve(int U, int V)
    {
        int ans = INT_MAX;
        int L = 0, R = 0;
        fa.assign(n + 5, 0);
        dep.assign(n + 5, 0);
        vis.assign(n + 5, false);
        dep[U] = 1;
        dep[V] = 2;
        vis[V] = true;
        queue<int> q;
        fa[V] = U;
        q.push(U), q.push(V);
        auto calc = [&](int x, int y)
        {
            if (dep[x] < dep[y])
                swap(x, y);
            int res = 0;
            while (dep[x] > dep[y])
            {
                res++;
                x = fa[x];
            }
            while (x != y)
            {
                res += 2;
                x = fa[x], y = fa[y];
            }
            return res;
        };
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : g[u])
            {
                if (!dep[v])
                {
                    dep[v] = dep[u] + 1;
                    vis[v] = vis[u];
                    fa[v] = u;
                    q.push(v);
                }
            }
        }
        for (int u = 1; u <= n; ++u)
        {
            for (int v : g[u])
            {
                if (vis[u] || vis[v])
                {
                    int now = calc(u, v);
                    if (now > 1 && now < ans)
                    {
                        ans = now;
                        if (vis[u])
                            L = u, R = v;
                        else
                            L = v, R = u;
                    }
                }
            }
        }
        if (ans == INT_MAX)
            return false;
        vis.assign(n + 5, 0);
        vis[U] = true;
        for (int u = R; fa[u]; u = fa[u])
        {
            edges[mp[{u, fa[u]}]] = {u, fa[u]};
            vis[u] = true;
        }
        for (int u = L; fa[u]; u = fa[u])
        {
            edges[mp[{fa[u], u}]] = {fa[u], u};
            vis[u] = true;
        }
        // cerr << "FUCK" << L << ' ' << R << endl;
        edges[mp[{L, R}]] = {L, R};
        for (auto [fuck, id] : mp)
        {
            auto [u, v] = fuck;
            if (vis[u])
                continue;
            else
            {
                if (vis[v])
                    edges[id] = {u, v};
                else
                    edges[id] = {u, v};
            }
        }
        return true;
    }
    auto print()
    {
        cout << "Yes\n";
        for (int i = 1; i <= m; ++i)
        {
            auto [u, v] = edges[i];
            // assert(u && v);
            cout << u << ' ' << v << '\n';
        }
    }
    Main()
    {
        cin >> n >> m >> S >> T;
        g.resize(n + 5);
        edges.resize(m + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            mp[{u, v}] = mp[{v, u}] = i;
        }
        if (!mp[{S, T}])
        {
            for (int v : g[S])
                edges[mp[{S, v}]] = {v, S};
            for (int v : g[T])
                edges[mp[{T, v}]] = {v, T};
            for (int u = 1; u <= n; ++u)
            {
                if (u == S || u == T)
                    continue;
                for (int v : g[u])
                {
                    if (v == S || v == T)
                        continue;
                    edges[mp[{u, v}]] = {u, v};
                }
            }
            print();
            return;
        }
        if (solve(S, T))
            print();
        else if (solve(T, S))
            print();
        else
            cout << "No\n";
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
