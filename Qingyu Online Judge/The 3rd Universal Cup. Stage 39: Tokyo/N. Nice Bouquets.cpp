#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int N = 2e5 + 5;
auto _main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 5, vector<int>(m + 5));
    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j)
            a[i][j] = (s[j] == 'R' ? 0 : (s[j] == 'G' ? 1 : 2));
        a[i][m] = 1;
    }
    auto add = [&](auto &x, const auto &y)
    {
        for (int i = 0; i <= m; ++i)
            (x[i] += y[i]) %= 3;
    };
    auto del = [&](auto &x, const auto &y)
    {
        for (int i = 0; i <= m; ++i)
            (x[i] += 3 - y[i]) %= 3;
    };
    vector<array<vector<int>, 2>> d(m + 5);
    auto insert = [&](auto x)
    {
        for (int i = m; i >= 0; --i)
            if (x[i])
            {
                if (d[i][x[i]].empty())
                {
                    d[i][x[i]] = x;
                    return true;
                }
                else
                    del(x, d[i][x[i]]);
            }
        return false;
    };
    auto check = [&](auto x)
    {
        for (int i = m; i >= 0; --i)
            if (x[i])
            {
                if (d[i][x[i]].empty())
                    return false;
                else
                    del(x, d[i][x[i]]);
            }
        return true;
    };
    vector<vector<int>> suf(n + 5, vector<int>(m + 5));
    for (int i = n; i >= 1; --i)
        add(suf[i] = suf[i + 1], a[i]);
    if (check(suf[1]))
    {
        cout << "0\n";
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        vector<int> b = a[i];
        add(b, a[i]);
        insert(a[i]);
        insert(b);
        if (check(suf[i + 1]))
        {
            cout << i << '\n';
            return;
        }
    }
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
