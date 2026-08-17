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
    int n, m, k;
    vector<vector<int>> g;
    auto dijkstra(const vector<int> &points)
    {
        if (points.empty())
            return true;
        queue<tuple<int, int, int>> q;
        vector<pair<int, int>> dis1(n + 5), dis2(n + 5);
        for (int i : points)
        {
            dis1[i].second = i;
            q.emplace(dis1[i].first, dis1[i].second, i);
        }
        while (!q.empty())
        {
            auto [d, p, u] = q.front();
            q.pop();
            if (d >= k - 1)
                break;
            for (int v : g[u])
            {
                if (!dis1[v].second)
                {
                    dis1[v] = make_pair(d + 1, p);
                    q.emplace(dis1[v].first, dis1[v].second, v);
                }
                else if (dis1[v].second != p && !dis2[v].second)
                {
                    if (dis1[v].second == v)
                        return false;
                    dis2[v] = make_pair(d + 1, p);
                    q.emplace(dis2[v].first, dis2[v].second, v);
                }
            }
        }
        return true;
    }
    Main()
    {
        cin >> n >> m >> k;
        g.resize(n + 5);
        array<vector<int>, 51> G;
        for (int i = 1; i <= n; ++i)
        {
            int c;
            cin >> c;
            G[c].push_back(i);
        }
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }
        for (int i = 1; i <= 50; ++i)
            if (!dijkstra(G[i]))
            {
                cout << "NO\n";
                return;
            }
        cout << "YES\n";
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

