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
struct Main
{
    int n;
    vector<int> d;
    vector<int> anc, fa;
    vector<int> mp;
    vector<int> dep;
    vector<vector<int>> g, h;
    vector<pair<int, int>> p;
    vector<bool> lock;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[_fa] + 1;
        anc[u] = mp[dep[u]];
        if (d[u] != -1)
        {
            d[u] += dep[u];
            if (d[u] <= n)
            {
                fa[u] = mp[d[u]];
                mp[d[u]] = u;
            }
            lock[u] = true;
        }
        else
            d[u] = INT_MAX;

        {
            auto it = lower_bound(p.begin(), p.end(), make_pair(dep[u], INT_MAX), greater<>());
            if (it != p.begin())
                h[prev(it)->second].push_back(u);
        }

        stack<pair<int, int>> store;
        while (!p.empty() && p.back().first <= d[u])
        {
            store.emplace(p.back());
            p.pop_back();
        }
        p.emplace_back(d[u], u);
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
        }
        p.pop_back();
        while (!store.empty())
        {
            p.emplace_back(store.top());
            store.pop();
        }
        if (d[u] <= n)
            mp[d[u]] = fa[u];
    }
    vector<int> in;
    Main()
    {
        cin >> n;
        d.resize(n + 5);
        anc.resize(n + 5), fa.resize(n + 5);
        mp.resize(n + 5);
        dep.resize(n + 5);
        g.resize(n + 5), h.resize(n + 5);
        lock.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> d[i];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        dfs(1, 0);
        in.resize(n + 5);
        for (int u = 1; u <= n; ++u)
            for (int v : h[u])
                ++in[v];
        priority_queue<int, vector<int>, greater<int>> q;
        for (int u = 1; u <= n; ++u)
            if (!in[u] && !lock[u])
                q.push(u);
        vector<int> answer;
        while (!q.empty())
        {
            int u = q.top();
            q.pop();
            answer.push_back(u);
            for (int v = anc[u]; v && lock[v]; v = fa[v])
            {
                lock[v] = false;
                if (!in[v] && !lock[v])
                    q.emplace(v);
            }
            for (int v : h[u])
                if (!--in[v] && !lock[v])
                    q.emplace(v);
        }
        // for (int u = 1; u <= n; ++u)
        // {
        //     for (int v : h[u])
        //         cout << u << ' ' << v << '\n';
        // }
        if ((int)answer.size() == n)
        {
            for (int v : answer)
                cout << v << ' ';
            cout << '\n';
        }
        else
            cout << "-1\n";
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
