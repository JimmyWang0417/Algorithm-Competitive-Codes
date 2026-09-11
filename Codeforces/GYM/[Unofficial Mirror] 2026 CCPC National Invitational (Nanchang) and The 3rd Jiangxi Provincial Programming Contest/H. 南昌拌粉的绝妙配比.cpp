#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n, m, A, B;
    vector<tuple<int, int, int>> a;
    i64 res = -1;
    auto dfs(int u, i64 X, i64 Y, i64 Z)
    {
        if (u == n)
        {
            if (X && Z <= m && X * B == Y * A)
                res = max(res, X);
            return;
        }
        dfs(u + 1, X, Y, Z);
        auto [x, y, z] = a[u];
        dfs(u + 1, X + x, Y + y, Z + z);
    }
    Main()
    {
        cin >> n >> m >> A >> B;
        a.resize(n);
        for (auto &[x, y, z] : a)
            cin >> x >> y >> z;
        dfs(0, 0, 0, 0);
        cout << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}