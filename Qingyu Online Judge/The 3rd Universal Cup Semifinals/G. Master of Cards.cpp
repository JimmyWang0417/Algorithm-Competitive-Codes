#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
auto _main()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(3 * n + 5);
    vector<int> dep(3 * n + 5);
    for (int i = 1; i <= n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        b += n, c += 2 * n;
        g[a].emplace_back(b, i * 3);
        g[b].emplace_back(a, i * 3);

        g[a].emplace_back(c, i * 3 + 1);
        g[c].emplace_back(a, i * 3 + 1);

        g[b].emplace_back(c, i * 3 + 2);
        g[c].emplace_back(b, i * 3 + 2);

        // cout << a << ' ' << b << '\n';
        // cout << a << ' ' << c << '\n';
        // cout << b << ' ' << c << '\n';
    }
    vector<pair<int, int>> answer;
    function<bool(int, int, int)> dfs = [&](int u, int _fa, int lasedge)
    {
        dep[u] = dep[_fa] + 1;
        vector<int> edge;
        for (auto [v, i] : g[u])
        {
            if (i == lasedge)
                continue;
            if (!dep[v])
            {
                if (dfs(v, u, i))
                    edge.emplace_back(i / 3);
            }
            else if (dep[v] > dep[u])
                edge.emplace_back(i / 3);
        }
        if (edge.size() & 1)
        {
            if (lasedge)
                edge.emplace_back(lasedge / 3);
            for (int i = 1; i < (int)edge.size(); i += 2)
                answer.emplace_back(edge[i - 1], edge[i]);
            return false;
        }
        else
        {
            for (int i = 1; i < (int)edge.size(); i += 2)
                answer.emplace_back(edge[i - 1], edge[i]);
            return true;
        }
    };
    for (int i = 1; i <= 3 * n; ++i)
    {
        if (dep[i])
            continue;
        dfs(i, 0, 0);
    }
    cout << answer.size() << '\n';
    for (auto [x, y] : answer)
        cout << x << ' ' << y << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}
