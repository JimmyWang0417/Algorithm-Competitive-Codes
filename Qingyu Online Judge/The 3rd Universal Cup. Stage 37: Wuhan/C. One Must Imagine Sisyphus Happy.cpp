#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m;
int a[N];
ll sum[N];
tuple<int, int, int> add[N];
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i < n; ++i)
    {
        int x = a[i] / (2 * n - 1), y = a[i] % (2 * n - 1);
        if (2 * (n - i) > y)
        {
            if (2 * i - 1 > y)
                ++get<0>(add[min(x, m)]);
            else
                ++get<1>(add[min(x, m)]);
        }
        else
            ++get<2>(add[min(x, m)]);
    }
    {
        int x = a[n] / (2 * n - 1);
        ++get<2>(add[min(x, m)]);
    }
    for (int i = 0; i <= m; ++i)
    {
        auto [x, y, z] = add[i];
        if (x)
            for (int j = 1, k = 0; j <= m; j += i + ((k++) & 1))
                sum[j] += x;
        if (y)
            for (int j = 1, k = 0; j <= m; j += i + (k++ != 0))
                sum[j] += y;
        if (z)
            for (int j = 1; j <= m; j += i + 1)
                sum[j] += z;
    }
    for (int i = 1; i <= m; ++i)
        cout << sum[i] << ' ';
    cout << '\n';
    for (int i = 0; i <= m; ++i)
    {
        sum[i] = 0;
        add[i] = make_tuple(0, 0, 0);
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}