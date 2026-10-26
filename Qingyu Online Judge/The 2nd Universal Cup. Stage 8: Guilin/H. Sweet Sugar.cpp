#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n, m;
    vector<int> a;
    vector<vector<int>> G;
    int answer = 0;
    auto dfs(int u, int _fa) -> pair<int, int>
    {
        int X, Y;
        if (a[u] % 2 == 0)
            X = a[u], Y = INT_MIN / 2;
        else
            X = INT_MIN / 2, Y = a[u];
        for (auto v : G[u])
        {
            if (v == _fa)
                continue;
            auto [x, y] = dfs(v, u);
            int XX = max({INT_MIN / 2, X, X + x, Y + y});
            int YY = max({INT_MIN / 2, Y, X + y, x + Y});
            X = XX, Y = YY;
        }
        if ((X % 2 == m % 2 && X >= m) || (Y % 2 == m % 2 && Y >= m))
        {
            ++answer;
            X = 0, Y = INT_MIN / 2;
        }
        return {X, Y};
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n + 5);
        G.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dfs(1, 0);
        cout << answer << '\n';
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
