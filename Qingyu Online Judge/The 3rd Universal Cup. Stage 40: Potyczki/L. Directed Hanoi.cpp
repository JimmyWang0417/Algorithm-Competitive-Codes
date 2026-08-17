#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
auto _main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 5);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }
    vector<vector<bool>> reach(n + 5, vector<bool>(n + 5));
    vector<vector<int>> dis(n + 5, vector<int>(n + 5));
    for (int i = n; i >= 1; --i)
    {
        reach[i][i] = true;
        for (auto j : g[i])
            for (int k = 1; k <= n; ++k)
                reach[i][k] = reach[i][k] | reach[j][k];
    }
    for (int i = n; i >= 1; --i)
        for (int j = i + 1; j <= n; ++j)
        {
            if (!reach[i][j])
                continue;
            dis[i][j] = 1;
            for (int k = i + 1; k < j; ++k)
                dis[i][j] += min(dis[i][k], dis[k][j]);
        }
    cout << dis[1][n] << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
