#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 6;
auto _main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(limit + 5, vector<int>(n + 5));
    auto update = [&](auto &&update, int d, int x, int y)
    {
        if (x <= 0)
            return;
        if (d < limit)
            update(update, d + 1, a[d][x], -1);
        a[d][x] += y;
        if (d < limit)
            update(update, d + 1, a[d][x], 1);
    };
    for (int i = 1; i <= n; ++i)
        cin >> a[0][i];
    for (int j = 1; j <= limit; ++j)
        for (int i = 1; i <= n; ++i)
            ++a[j][a[j - 1][i]];
    int block = min((int)sqrt(2 * n) + 5, n);
    while (m--)
    {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1)
        {
            update(update, 1, a[0][x], -1);
            update(update, 1, a[0][x] = y, 1);
        }
        else
        {
            if (x <= limit)
                cout << a[x][y] << '\n';
            else
            {
                vector<int> p;
                p.resize(block + 1);
                for (int i = 1; i <= block; ++i)
                    p[i] = a[limit][i];
                for (int j = limit + 1; j <= 12 && j <= x; ++j)
                {
                    int len = *max_element(p.begin() + 1, p.end());
                    vector<int> q(max(len, 1) + 1, 0);
                    for (int i = 1; i < (int)p.size(); ++i)
                        if (p[i])
                            ++q[p[i]];
                    swap(p, q);
                }
                if (x <= 12)
                    cout << (y >= (int)p.size() ? 0 : p[y]) << '\n';
                else
                    cout << (y == 1 && p[1] == 1) << '\n';
            }
        }
    }
}
signed main()
{
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
