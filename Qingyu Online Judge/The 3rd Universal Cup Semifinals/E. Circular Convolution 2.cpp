#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
auto _main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < n; ++i)
    {
        a[i].first -= a[0].first;
        a[i].second = (a[i].second - a[0].second + n) % n;
    }
    vector<int> f(n, INT_MAX / 2);
    f[0] = 0;
    for (int i = 1; i < 100 && i < n; ++i)
    {
        int d = gcd(n, a[i].second);
        for (int T = 0; T < 2; ++T)
            for (int r = 0; r < d; ++r)
            {
                for (int j = 0, x = r, y = (r + a[i].second) % n; j < n / d; ++j, x = y, (y += a[i].second) %= n)
                    f[y] = min(f[y], f[x] + a[i].first);
            }
    }
    for (int i = 0; i < n; ++i)
        cout << f[i] + (i64)n * a[0].first << ' ';
    cout << '\n';
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
