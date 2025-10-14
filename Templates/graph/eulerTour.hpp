#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct eulerTour
{ // 字典序最小
    vector<int> p;
    eulerTour() = default;
    eulerTour(int n, const vector<pair<int, int>> &edges)
    {
        vector<vector<int>> g(n + 5);
        vector<int> in(n + 5), out(n + 5);
        for (auto [u, v] : edges)
        {
            g[u].push_back(v);
            ++out[u], ++in[v];
        }
        for (int i = 1; i <= n; ++i)
            sort(g[i].begin(), g[i].end(), greater<int>());
        int S = 1, cnt0 = 0, cnt1 = 0;
        for (int u = 1; u <= n; ++u)
        {
            if (in[u] == out[u])
                continue;
            if (out[u] - in[u] == 1)
            {
                S = u;
                ++cnt0;
            }
            else if (in[u] - out[u] == 1)
                ++cnt1;
            else
                return;
        }
        if (!(cnt0 == cnt1 && cnt0 <= 1))
            return;
        p.reserve(n);
        function<void(int)> dfs = [&](int u)
        {
            while (!g[u].empty())
            {
                int v = g[u].back();
                g[u].pop_back();
                dfs(v);
            }
            p.push_back(u);
        };
        dfs(S);
        reverse(p.begin(), p.end());
    }
};
struct Main
{
    Main()
    {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m);
        for (auto &[u, v] : edges)
            cin >> u >> v;
        eulerTour tour(n, edges);
        if (tour.p.empty())
            cout << "No\n";
        else
        {
            for (int i : tour.p)
                cout << i << ' ';
            cout << '\n';
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}