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
    int n, m, q;
    vector<int> a;
    vector<vector<pair<int, int>>> g;
    vector<i64> dist, dis;
    vector<i64> belong;
    auto init()
    {
        vector<bool> vis(n + 5);
        dist.assign(n + 5, LONG_LONG_MAX);
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> que;
        que.emplace(dist[1] = 0, 1);
        while (!que.empty())
        {
            int u = que.top().second;
            que.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            for (auto [v, w] : g[u])
                if (dist[v] > dist[u] + w)
                    que.emplace(dist[v] = dist[u] + w, v);
        }
    }
    auto solve()
    {
        vector<bool> vis(n + 5);
        dis.assign(n + 5, LONG_LONG_MAX);
        belong.resize(n + 5);
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> que;
        for (int i = 0; i < (int)a.size(); ++i)
        {
            que.emplace(dis[a[i]] = 0, a[i]);
            belong[a[i]] = i;
        }
        while (!que.empty())
        {
            int u = que.top().second;
            que.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            for (auto [v, w] : g[u])
                if (dis[v] > dis[u] + w)
                {
                    belong[v] = belong[u];
                    que.emplace(dis[v] = dis[u] + w, v);
                }
        }
    }
    Main()
    {
        cin >> n >> m >> q;
        a.resize(q);
        for (int &i : a)
            cin >> i;
        g.resize(n + 5);
        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].emplace_back(v, w * 2);
            g[v].emplace_back(u, w * 2);
        }
        init();
        solve();
        i64 tme = 0;
        for (int i : a)
            tme = max(tme, dist[i]);
        vector<i64> answer(q);
        for (int u = 1; u <= n; ++u)
        {
            for (auto [v, w] : g[u])
            {
                if (belong[u] == belong[v])
                    continue;
                if (dis[u] > dis[v])
                    continue;
                auto calc = [&]() -> i64
                {
                    auto meetv = (w - (dis[v] - dis[u])) / 2, meetu = w - meetv;
                    if (min(dis[u] + meetu * 2 + dist[u], dis[v] + meetv * 2 + dist[v]) > tme)
                        return 0;
                    return tme - (dis[u] + meetu);
                };
                auto res = calc();
                answer[belong[u]] = max(answer[belong[u]], res);
                answer[belong[v]] = max(answer[belong[v]], res);
            }
        }
        for (auto i : answer)
            cout << (double)i / 2 << ' ';
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(1);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
